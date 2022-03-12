#include "chatserver.h"
#include "service.h"
#include <iostream>
#include <signal.h>

using namespace std;

void resetHandler(int)
{
    Service::instance()->reset();
    exit(0);
}
int main()
{
    signal(SIGINT, resetHandler);
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    
} 