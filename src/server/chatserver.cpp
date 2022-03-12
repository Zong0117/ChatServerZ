#include "chatserver.h"
#include "service.h"
#include <functional>
#include <muduo/base/Logging.h>

#include "json.hpp"
using json = nlohmann::json;

using namespace std;
using namespace placeholders;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : _server(loop, listenAddr, nameArg), _loop(loop)
{
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    LOG_INFO << "SERVER START!";
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    if(!conn->connected())
    {
        Service::instance()->clientCloseException(conn);
        LOG_INFO << "IP: " << conn->peerAddress().toIpPort() << "";
        conn->shutdown();
    }   
    LOG_INFO << "IP: " << conn->peerAddress().toIpPort() << "SUCESSES CONNECTED";    
}
void ChatServer::onMessage(const TcpConnectionPtr& conn,
                           Buffer* buffer,
                           Timestamp time)
{
    std::string buf = buffer->retrieveAllAsString();
    json js = json::parse(buf);
    //接收消息 通过消息内msgid使handler处理对应工作
    auto msgHandler = Service::instance()->getHandler(js["msgID"].get<int>());
    msgHandler(conn, js, time);
}