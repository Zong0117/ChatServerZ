#pragma once
#include <string>
#include <vector>
class OffLineMSGModel
{
public:
    //向数据库写入用户离线消息
    void insert(int, std::string);

    //删除离线消息
    void remove(int);

    //查询用户离线消息
    std::vector<std::string> query(int);

};