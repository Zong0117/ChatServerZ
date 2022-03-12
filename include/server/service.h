#include <unordered_map>
#include <functional>
#include <mutex>

#include <muduo/net/TcpConnection.h>
using namespace muduo::net;
using namespace muduo;

#include "usermodel.h"
#include "msgmodel.h"
#include "friendmodel.h"
#include "groupmodel.h"

#include "json.hpp"
using json = nlohmann::json;

//处理消息的事件回调类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp time)>;

class Service
{
public:
    //处理业务的单元同时间只需要存在一个实例，所以设计为单例
    static Service* instance();

    //服务端异常退出重置state
    void reset();

    //登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //注册业务
    void regis(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //根据业务码 去handlermap里寻找相应的业务回调函数并返回
    MsgHandler getHandler(int);

    //处理客户端异常退出
    void clientCloseException(const TcpConnectionPtr&);

    //一对一聊天
    void privateChat(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //添加好友功能
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    
    //创建群
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //加入群
    void joinGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //群发消息
    void sendGroupMessage(const TcpConnectionPtr &conn, json &js, Timestamp time);

private:
    Service();

    //绑定业务码和操作函数
    //int:业务的msg, mgsHandler:业务的具体操作
    std::unordered_map<int, MsgHandler> _msgHandlerMap; 

    //记录用户的连接
    //int:用户id conn连接
    //会在运行中改变内容，需注意线程安全
    std::unordered_map<int, TcpConnectionPtr> _userConnMap; 

    //保证修改connMap时的线程安全
    std::mutex _connMutex;

    UserModel _userModel;

    OffLineMSGModel _offLineMSGModel;

    FriendModel _friendModel;

    GroupModel _groupModel;
};