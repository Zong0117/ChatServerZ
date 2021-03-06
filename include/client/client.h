#pragma once

#include "json.hpp"
#include "user.h"
#include "group.h"
#include "msgtype.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <atomic>
#include <semaphore.h>

using namespace std;
using namespace std::placeholders;
using json = nlohmann::json;

class Client
{
public:
    Client();
    //显示当前用户信息
    void showCurrentUserInfo();
    //主页面显示
    void mainMenu();
    //接收数据线程
    void readTackHandler();
    //获取系统时间
    std::string getTime();
    //客户端主体程序
    void clientStart(char *, unsigned int);
    //处理登录响应
    void doLoginResponse(json&);
    //处理注册响应
    void doRegisResponse(json&);
    string getCurrentTime();
public:
    // "help" 
    void help(string);
    // "chat"
    void chat(string);
    // "addfriend"
    void addFriend(string);
    // "creategroup"
    void createGroup(string);
    // "addgroup" 
    void joinGroup(string);
    // "groupchat" 
    void groupChat(string);
    // "loginout"
    void loginout(string);
public:
    static int readThreadNumb;
private:

    int _clientFD;

    bool _isMainMenuRunning = false;
    //读写线程通信
    sem_t _rwsem;
    //记录登陆状态
    atomic<bool> _isLoginSuccess{false};
    //记录当前用户信息
    User _currentUser;
    //记录当前用户好友信息
    std::vector<User> _currentFriend;

    //记录当前用户群组信息
    std::vector<Group> _currentGroup;

    const unordered_map<string, string> _commandMap = {

        {"help", "显示所有支持的命令，格式help"},
        {"chat", "一对一聊天，格式chat:friendid:message"},
        {"addfriend", "添加好友，格式addfriend:friendid"},
        {"creategroup", "创建群组，格式creategroup:groupname:groupdesc"},
        {"joingroup", "加入群组，格式joingroup:groupid"},
        {"groupchat", "群聊，格式groupchat:groupid:message"},
        {"loginout", "注销，格式loginout"}};

    unordered_map<string, function<void(string)>> _commandHandlerMap;

};