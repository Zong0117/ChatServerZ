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
int main(int argc, char** argv)
{
    char* ip = argv[1];
    int port = atoi(argv[2]);
    signal(SIGINT, resetHandler);
    EventLoop loop;
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    
} 