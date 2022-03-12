#include "friendmodel.h"
#include "../../include/server/db/db.h"
//添加好友
void FriendModel::insert(int userID, int friendID)
{
    char sql[1024] = {0};
    sprintf(sql, 
    "insert into friend(userid, friendid) values(%d, %d)",userID, friendID);

    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }
}

//返回用户好友列表
std::vector<User> FriendModel::query(int userID)
{
    char sql[1024] = {0};
    sprintf(sql,
    "select u.id, u.name, u.state from user u inner join friend f on f.friendid = u.id where f.userid = %d",
    userID);

    std::vector<User> vec;
    MySQL mysql;

    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            } 
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}