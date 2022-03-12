#include "msgmodel.h"
#include "../../include/server/db/db.h"

//向数据库写入用户离线消息
void OffLineMSGModel::insert(int userId, std::string msg)
{
    char sql[1024] = {0};
    sprintf(sql, 
    "insert into off_line_message(userid, message) value(%d,'%s')", userId, msg.c_str());
    
    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }

}

//删除离线消息
void OffLineMSGModel::remove(int userId)
{
    char sql[1024] = {0};
    sprintf(sql,
    "delete from off_line_message where userid = %d", userId);

    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }
}

//查询用户离线消息
std::vector<std::string> OffLineMSGModel::query(int userId)
{
    char sql[1024] = {0};
    sprintf(sql,
    "select message from off_line_message where userid = %d", userId);

    vector<string> vec;
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;

}