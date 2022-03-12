#pragma once

#include "user.h"
#include <vector>

class FriendModel
{
public:
    //添加好友
    void insert(int userID, int friendID);
    // //删除好友关系
    // void remove();
    //返回用户好友列表
    std::vector<User> query(int userID);
};