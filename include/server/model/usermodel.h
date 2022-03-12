#pragma once

#include "user.h"

//user表的数据操作类
class UserModel
{
public:
    //向数据库插入用户信息
    bool insert(User& user);

    //根据id查询用户信息
    User query(int id);

    //更新用户状态信息
    bool updateState(User user);

    //服务端异常退出重置state
    void resetState();
    
};