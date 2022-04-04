#include "client.h"
#include "json.hpp"
#include "msgtype.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <thread>


int Client::readThreadNumb = 0;
Client::Client()
{
    _commandHandlerMap.insert({"help", std::bind(&Client::help, this, _1)});
    _commandHandlerMap.insert({"chat", std::bind(&Client::chat, this, _1)});
    _commandHandlerMap.insert({"addfriend", std::bind(&Client::addFriend, this, _1)});
    _commandHandlerMap.insert({"creategroup", std::bind(&Client::createGroup, this, _1)});
    _commandHandlerMap.insert({"joingroup", std::bind(&Client::joinGroup, this, _1)});
    _commandHandlerMap.insert({"groupchat", std::bind(&Client::groupChat, this, _1)});
    _commandHandlerMap.insert({"loginout", std::bind(&Client::loginout, this, _1)});
}
//显示当前用户信息
void Client::showCurrentUserInfo()
{
    cout << "======================登陆信息=====================" << endl;
    cout << "--当前用户为：" << _currentUser.getName() << " id: " << _currentUser.getId() << endl;
    cout << "=======================好友列表====================" << endl;
    if (!_currentFriend.empty())
    {
        for (auto user : _currentFriend)
        {
            cout << "用户名:  " << user.getName() << "id: " << user.getId() << " 当前状态：" << user.getState() << endl;
        }
    }
    cout << "=======================群组列表====================" << endl;
    if (!_currentGroup.empty())
    {
        for (auto group : _currentGroup)
        {
            cout << "group: " << group.getGroupID() << " " << group.getGroupName() << " " << group.getGroupDesc() << endl;
            for (auto user : group.getGroupUser())
            {
                cout << user.getId() << " " << user.getName() << " "
                     << user.getState() << " " << user.getGroupRole() << endl;
                ;
            }
        }
    }
}
//主页面显示
void Client::mainMenu()
{
    help("");
    char buffer[1024] = {0};
    while (_isMainMenuRunning)
    {
        cin.getline(buffer, 1024);
        string commandbuf(buffer);
        string command; // 存储命令
        int idx = commandbuf.find(":");
        if (-1 == idx)
        {
            command = commandbuf;
        }
        else
        {
            command = commandbuf.substr(0, idx);
        }
        auto it = _commandHandlerMap.find(command);
        if (it == _commandHandlerMap.end())
        {
            cerr << "invalid input command!" << endl;
            continue;
        }

        // 调用相应命令的事件处理回调，mainMenu对修改封闭，添加新功能不需要修改该函数
        it->second(commandbuf.substr(idx + 1, commandbuf.size() - idx)); // 调用命令处理方法
    }
}
//接收数据线程
void Client::readTackHandler()
{
    while (1)
    {
        char buffer[1024] = {0};
        int len = recv(_clientFD, buffer, 1024, 0); //阻塞等待
        if (len == -1 || len == 0)
        {
            close(_clientFD);
            exit(-1);
        }

        json js = json::parse(buffer);
        int msgType = js["msgID"].get<int>();

        if (PRI_CHAT_MSG == msgType)
        {
            cout << js["time"].get<string>() << " [" << js["userID"] << "] "
                 << js["userName"].get<string>() << " : " << js["msg"].get<string>() << endl;
            continue;
        }

        if (SEND_GROUP_MSG == msgType)
        {
            cout << "群消息[ " << js["groupID"] << " ]:" << js["time"].get<string>() << " [" << js["userID"] << "] "
                 << js["userName"].get<string>() << " : " << js["msg"].get<string>() << endl;
            continue;
        }

        if (LOGIN_ACK == msgType)
        {
            doLoginResponse(js); //处理登录业务
            sem_post(&_rwsem);   //通知主线程 登陆处理完成
            continue;
        }

        if (REGIS_ACK == msgType)
        {
            doRegisResponse(js); //处理登录业务
            sem_post(&_rwsem);   //通知主线程 注册处理完成
            continue;
        }
    }
}
//获取系统时间
std::string Client::getTime()
{
}
//客户端主体程序
void Client::clientStart(char *ip, unsigned int port)
{

    _clientFD = socket(AF_INET, SOCK_STREAM, 0);
    if (_clientFD == -1)
    {
        cerr << "socket creat error!" << endl;
        exit(-1);
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int flag = connect(_clientFD, (sockaddr *)&addr, sizeof(sockaddr_in));
    if (flag == -1)
    {
        cerr << "connect error" << endl;
        close(_clientFD);
        exit(-1);
    }

    //初始化读写信号量
    sem_init(&_rwsem, 0, 0);

    //服务连接成功创建子线程专门接收数据
    thread readTask(&Client::readTackHandler, this);
    readTask.detach();

    while (1)
    {
        cout << "============" << endl;
        cout << " 登录 : 1" << endl;
        cout << " 注册 : 2" << endl;
        cout << " 退出 : 3" << endl;
        cout << "============" << endl;
        cout << "请选择：" << endl;
        int input;
        cin >> input;
        cin.get();
        system("clear");
        switch (input)
        {
        case 1:
        {
            int id = -1;
            char password[50] = {0};
            cout << "输入id:" << endl;
            cin >> id;
            cin.get();
            cout << "输入密码:" << endl;
            cin.getline(password, 50);
            system("clear");

            json js;
            js["msgID"] = LOGIN_MSG;
            js["userID"] = id;
            js["password"] = password;
            string request = js.dump();

            //初始化登陆变量
            _isLoginSuccess = false;

            int len = send(_clientFD, request.c_str(), strlen(request.c_str()) + 1, 0);

            if (len == -1)
            {
                cerr << "发送登录消息失败" << endl;
            }

            //等待信号量 子线程处理完登录的响应后通知
            sem_wait(&_rwsem);

            if (_isLoginSuccess)
            {
                //进入聊天主页面
                _isMainMenuRunning = true;
                mainMenu();
            }
        }
            system("clear");
            break;
        case 2:
        {
            char name[50] = {0};
            char password[50] = {0};
            cout << "输入用户名:" << endl;
            cin.getline(name, 50);
            cout << "输入密码:" << endl;
            cin.getline(password, 50);

            json js;
            js["msgID"] = REGIS_MSG;
            js["userName"] = name;
            js["password"] = password;
            string request = js.dump();

            int len = send(_clientFD, request.c_str(), strlen(request.c_str()) + 1, 0);

            if (len == -1)
            {
                cerr << "发送注册消息失败" << endl;
            }
            //子线程处理完注册消息会通知
            sem_wait(&_rwsem);
        }
            system("clear");
            break;
        case 3:
            system("clear");
            close(_clientFD);
            sem_destroy(&_rwsem);
            exit(0);
        default:
            cout << "非法输入" << endl;
            system("clear");
            break;
        }
    }
}

string Client::getCurrentTime()
{
}

// "help" command handler
void Client::help(string str)
{
    cout << "命令列表： >>> " << endl;
    for (auto &p : _commandMap)
    {
        cout << p.first << " : " << p.second << endl;
    }
    cout << endl;
}
// "chat" command handler
void Client::chat(string str)
{
    int idx = str.find(":"); // friendid:message
    if (-1 == idx)
    {
        cerr << "聊天指令错误" << endl;
        return;
    }

    int friendid = atoi(str.substr(0, idx).c_str());
    string message = str.substr(idx + 1, str.size() - idx);

    json js;
    js["msgID"] = PRI_CHAT_MSG;
    js["userID"] = _currentUser.getId();
    js["userName"] = _currentUser.getName();
    js["toID"] = friendid;
    js["msg"] = message;
    js["time"] = getCurrentTime();
    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端聊天消息发送错误 -> " << buffer << endl;
    }
}
// "addfriend" command handler
void Client::addFriend(string str)
{
    int friendid = atoi(str.c_str());
    json js;
    js["msgID"] = ADD_FRIEND_MSG;
    js["userID"] = _currentUser.getId();
    js["friendID"] = friendid;

    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端添加好友消息发送错误 -> " << buffer << endl;
    }
}
// "creategroup" command handler
void Client::createGroup(string str)
{
    int idx = str.find(":"); // friendid:message
    if (-1 == idx)
    {
        cerr << "创建群组命令错误" << endl;
        return;
    }
    string groupName = str.substr(0, idx);
    string groupDesc = str.substr(idx + 1, str.size() - 1);
    json js;
    js["msgID"] = CREATE_GROUP_MSG;
    js["userID"] = _currentUser.getId();
    js["groupName"] = groupName;
    js["groupDesc"] = groupDesc;

    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端创建群组消息发送错误 ->" << buffer << endl;
    }
}
// "joingroup" command handler
void Client::joinGroup(string str)
{
    int groupID = atoi(str.c_str());

    json js;
    js["msgID"] = JOIN_GROUP_MSG;
    js["userID"] = _currentUser.getId();
    js["groupID"] = groupID;

    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端加入群组消息发送错误 ->" << buffer << endl;
    }
}
// "groupchat" command handler
void Client::groupChat(string str)
{
    int idx = str.find(":"); // friendid:message
    if (-1 == idx)
    {
        cerr << "群发消息命令错误" << endl;
        return;
    }
    int groupID = atoi(str.substr(0, idx).c_str());
    string message = str.substr(idx + 1, str.size() - idx);

    json js;
    js["msgID"] = SEND_GROUP_MSG;
    js["userID"] = _currentUser.getId();
    js["userName"] = _currentUser.getName();
    js["groupID"] = groupID;
    js["msg"] = message;
    js["time"] = getCurrentTime();
    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端群组聊天消息发送错误 -> " << buffer << endl;
    }
}
// "loginout" command handler
void Client::loginout(string str)
{
    json js;
    js["msgID"] = LOGIN_OUT_MSG;
    js["userID"] = _currentUser.getId();
    string buffer = js.dump();

    int len = send(_clientFD, buffer.c_str(), strlen(buffer.c_str()) + 1, 0);
    if (-1 == len)
    {
        cerr << "客户端用户注销消息发送错误 -> " << buffer << endl;
    }
    else
    {
        _isMainMenuRunning = false;
    }
}

//处理登录响应
void Client::doLoginResponse(json &response)
{
    if (response["code"].get<int>() != 0)
    {
        //登录失败
        cerr << "登录失败" << endl;
        _isLoginSuccess = false;
    }
    else
    {
        //登录成功
        _currentUser.setId(response["userID"].get<int>());
        _currentUser.setName(response["userName"]);

        //记录好友信息
        if (response.contains("friends"))
        {
            //初始化
            _currentFriend.clear();

            vector<string> vec = response["friends"];
            for (auto &str : vec)
            {
                json js = json::parse(str);
                User user;
                user.setId(js["userID"]);
                user.setName(js["userName"]);
                user.setState(js["userState"]);
                _currentFriend.push_back(user);
            }
        }

        //记录群组信息
        if (response.contains("groups"))
        {
            //初始化
            _currentGroup.clear();

            vector<string> vec = response["groups"];
            for (auto &str : vec)
            {
                json grpjs = json::parse(str);
                Group group;
                group.setGroupID(grpjs["groupID"]);
                group.setGroupName(grpjs["groupName"]);
                group.setGroupDesc(grpjs["groupDesc"]);
                vector<string> groupUserVec = grpjs["groupUsers"];
                //记录群组用户信息
                for (auto &user : groupUserVec)
                {
                    json js = json::parse(user);
                    GroupUser groupUser;
                    groupUser.setId(js["userID"]);
                    groupUser.setName(js["userName"]);
                    groupUser.setState(js["userState"]);
                    groupUser.setGroupRole(js["role"]);
                    group.getGroupUser().push_back(groupUser);
                }
                _currentGroup.push_back(group);
            }
        }

        showCurrentUserInfo();
        if (response.contains("msg"))
        {
            vector<string> msgVec = response["msg"];
            for (auto &msg : msgVec)
            {
                json js = json::parse(msg);
                int msgType = js["msgID"].get<int>();
                if (PRI_CHAT_MSG == msgType)
                {
                    cout << js["time"].get<string>() << " [" << js["userID"] << "] "
                         << js["userName"].get<string>() << " : " << js["msg"].get<string>() << endl;
                    continue;
                }
                if (SEND_GROUP_MSG == msgType)
                {
                    cout << "群消息[ " << js["groupID"] << " ]:" << js["time"].get<string>() << " [" << js["userID"] << "] "
                         << js["userName"].get<string>() << " : " << js["msg"].get<string>() << endl;
                    continue;
                }
            }
        }
        //登陆成功置为true
        _isLoginSuccess = true;
    }
}

//处理注册响应
void Client::doRegisResponse(json &response)
{
    if (response["code"].get<int>() != 0)
    {
        //注册失败
        cerr << "注册失败" << endl;
    }
    else
    {
        //注册成功
        cout << "注册成功" << endl;
        cout << "您的id为：" << response["userID"] << " 请记好您的id" << endl;
    }
}