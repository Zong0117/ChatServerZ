#include <iostream>

#include "../../include/server/db/db.h"
#include "usermodel.h"

using namespace std;

bool UserModel::insert(User &user)
{
    char sql[1024] = {0};
    sprintf(sql, 
    "insert into user(name, password, state) value('%s', '%s', '%s')", 
    user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());
    
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

User UserModel::query(int id)
{
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    MySQL mysql;
    if (mysql.connect())
    {
        //通过sql语句查询到内容 id为不可重复主键
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            //拿到这行数据
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }
        }
    }
    return User();
}

bool UserModel::updateState(User user)
{
    char sql[1024] = {0};
    
    sprintf(sql, "update user set state = '%s' where id = %d", 
    user.getState().c_str(), user.getId());

    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
           return true;
        }
    }
    return false;
}

 //服务端异常退出重置state
void UserModel::resetState()
{
    char sql[1024] = "update user set state = 'offline' where state = 'online'";

    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }
}   