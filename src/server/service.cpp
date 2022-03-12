#include <muduo/base/Logging.h>
#include "service.h"
#include "msgtype.h"
#include <vector>
#include <string>
#include <map>
Service::Service()
{
    //绑定登录的消息和对应回调
    _msgHandlerMap.insert({LOGIN_MSG, std::bind(&Service::login, this, _1, _2, _3)});
    //绑定注册消息和对应回调
    _msgHandlerMap.insert({REGIS_MSG, std::bind(&Service::regis, this, _1, _2, _3)});
    //绑定一对一聊天消息和对应回调
    _msgHandlerMap.insert({PRI_CHAT_MSG, std::bind(&Service::privateChat, this, _1, _2, _3)});
    //绑定添加好友消息和对应回调
    _msgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&Service::addFriend, this, _1, _2, _3)});
    //创建群
    _msgHandlerMap.insert({CREATE_GROUP_MSG, std::bind(&Service::createGroup, this, _1, _2, _3)});
    //加入群
    _msgHandlerMap.insert({JOIN_GROUP_MSG, std::bind(&Service::joinGroup, this, _1, _2, _3)});
    //群发消息
    _msgHandlerMap.insert({SEND_GROUP_MSG, std::bind(&Service::sendGroupMessage, this, _1, _2, _3)});
}

//线程安全
Service *Service::instance()
{
    static Service service;
    return &service;
}

//服务端异常退出重置state
void Service::reset()
{
    _userModel.resetState();
}

//登录业务
void Service::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "IP: " << conn->peerAddress().toIpPort() << "进行登录！";
    int id = js["userID"];
    string pwd = js["password"];
    //查询id是否已经注册
    User user = _userModel.query(id);
    //核对用户密码是否输入正确
    if (user.getId() == id, user.getPassword() == pwd)
    {
        //如果找到对应信息但状态为在线，判断为重复登陆
        if (user.getState() == "online")
        {
            //重复登陆情况
            json response;
            response["msgID"] = LOGIN_ACK;
            response["code"] = FAILD_NO;
            response["errMsg"] = "用户已是登录状态，请勿重复登陆";
            conn->send(response.dump());
        }
        else
        {

            { //线程安全
                std::lock_guard<std::mutex> lock(_connMutex);
                //记录下用户的连接信息
                _userConnMap.insert({id, conn});
            }

            //登陆成功 更新用户状态state
            user.setState("online");
            _userModel.updateState(user);

            json response;
            response["msgID"] = LOGIN_ACK;
            response["code"] = SUCCESS_NO;
            response["userID"] = user.getId();
            response["name"] = user.getName();

            //查询用户的离线消息
            std::vector<std::string> offLineMSGVec = _offLineMSGModel.query(id);
            if (!offLineMSGVec.empty())
            {
                response["offLineMessage"] = offLineMSGVec;
                _offLineMSGModel.remove(id);
            }

            //查询用户的好友信息
            std::vector<User> userVec = _friendModel.query(id);
            if (!userVec.empty())
            {
                std::vector<std::string> tempVec;
                for (auto &user : userVec)
                {
                    json js;
                    js["userID"] = user.getId();
                    js["name"] = user.getName();
                    js["state"] = user.getState();
                    tempVec.push_back(js.dump());
                }
                response["friend"] = tempVec;
            }
            //发送json数据
            conn->send(response.dump());

            LOG_INFO << "id: " << user.getId() << " 登陆成功！"
                     << "IP: " << conn->peerAddress().toIpPort();
        }
    }
    else
    {
        //登陆失败 用户不存在或用户存在或密码错误
        json response;
        response["msgId"] = LOGIN_ACK;
        response["code"] = FAILD_NO;
        response["errorMsg"] = "用户不存在或用户名密码错误！";
        conn->send(response.dump());
        LOG_INFO << "IP: " << conn->peerAddress().toIpPort()
                 << " 登录失败！";
    }
}
//注册业务
void Service::regis(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "IP: " << conn->peerAddress().toIpPort() << " 进行注册！";
    string name = js["name"];
    string pwd = js["password"];

    User user;
    user.setName(name);
    user.setPassword(pwd);

    bool isRegSuccess = _userModel.insert(user);
    if (isRegSuccess)
    {
        json response;
        response["msgId"] = REGIS_ACK;
        response["code"] = SUCCESS_NO;
        response["userId"] = user.getId();
        conn->send(response.dump());
        LOG_INFO << "IP: " << conn->peerAddress().toIpPort()
                 << " 注册成功!";
    }
    else
    {
        json response;
        response["msgId"] = REGIS_ACK;
        response["code"] = FAILD_NO;
        response["errorMsg"] = "注册失败";
        conn->send(response.dump());
        LOG_INFO << "IP: " << conn->peerAddress().toIpPort()
                 << " 注册失败!";
    }
}

MsgHandler Service::getHandler(int msgID)
{
    auto it = _msgHandlerMap.find(msgID);
    if (it == _msgHandlerMap.end())
    {
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time)
        {
            LOG_ERROR << "msgID: " << msgID << " 找不到对应的处理方式";
        };
    }
    else
    {
        return _msgHandlerMap[msgID];
    }
}
//处理客户端异常退出
void Service::clientCloseException(const TcpConnectionPtr &conn)
{
    User user;

    {
        std::lock_guard<std::mutex> lock(_connMutex);

        for (auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it)
        {
            if (it->second == conn)
            {
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }

    if (user.getId() != -1)
    {
        user.setState("offline");
        _userModel.updateState(user);
    }
}

//一对一聊天
void Service::privateChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int toid = js["toID"].get<int>();

    {
        std::lock_guard<std::mutex> lock(_connMutex);

        auto it = _userConnMap.find(toid);
        if (it != _userConnMap.end())
        {
            //找到id对应连接，表示连接在线 直接转发消息
            it->second->send(js.dump());
            return;
        }
        else
        {
            //离线消息存储
            _offLineMSGModel.insert(toid, js.dump());
        }
    }
    json response;
    response["msgID"] = PRI_CHAT_ACK;
    response["code"] = SUCCESS_NO;
    response["toID"] = toid;
    conn->send(response.dump());
}

//添加好友功能
void Service::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userID = js["userID"].get<int>();
    int friendID = js["friendID"].get<int>();

    _friendModel.insert(userID, friendID);

    json response;
    response["msgID"] = ADD_FRIEND_ACK;
    response["code"] = SUCCESS_NO;
    response["friendID"] = friendID;
    conn->send(response.dump());
}

//创建群
void Service::createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userID = js["userID"].get<int>();
    std::string groupName = js["groupName"];
    std::string groupDesc = js["groupDesc"];

    Group group(-1, groupName, groupDesc);

    if (_groupModel.createGroup(group))
    {
        _groupModel.addGroup(userID, group.getGroupID(), "Creator");

        json response;
        response["msgID"] = CREATE_GROUP_ACK;
        response["code"] = SUCCESS_NO;
        response["groupID"] = group.getGroupID();
        conn->send(response.dump());
    }
}

//加入群
void Service::joinGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userID = js["userID"].get<int>();
    int groupID = js["groupID"].get<int>();

    _groupModel.addGroup(userID, groupID, "Normal");

    json response;
    response["msgID"] = JOIN_GROUP_ACK;
    response["code"] = SUCCESS_NO;
    response["groupID"] = groupID;
    conn->send(response.dump());
}

//群发消息
void Service::sendGroupMessage(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userID = js["userID"].get<int>();
    int groupID = js["groupID"].get<int>();

    std::vector<int> userVec = _groupModel.queryGroupUsers(userID, groupID);
    {
        std::lock_guard<std::mutex> lock(_connMutex);
        for (auto id : userVec)
        {
            auto it = _userConnMap.find(id);
            if (it != _userConnMap.end())
            {
                conn->send(js.dump());
            }
            else
            {
                _offLineMSGModel.insert(id, js.dump());
            }
        }
    }

    json response;
    response["msgID"] = SEND_GROUP_ACK;
    response["code"] = SUCCESS_NO;
    response["groupID"] = groupID;
    conn->send(response.dump());
}