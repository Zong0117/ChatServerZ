#include <iostream>
#include "client.h"

using namespace std;

int main()
{
    // char ip[128] = {0};
    // int port = -1;
    // cout << "输入ip地址" << endl;
    // cin.getline(ip, 128);
    // cout << "输入端口号" << endl;
    // cin >> port;
    // cin.get();
    // system("clear");
    Client client;

    client.clientStart("127.0.0.1", 6000);
}