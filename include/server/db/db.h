#pragma once
#include <muduo/base/Logging.h>
#include <mysql/mysql.h>
#include <string>
#include <iostream>
using namespace std;

// 数据库操作类
class MySQL
{
public:
    // 初始化数据库连接
    MySQL();
    // 释放数据库连接资源
    ~MySQL();
    // 连接数据库
    bool connect();
    // 更新操作
    bool update(string sql);
    // 查询操作
    MYSQL_RES* query(string sql);

    inline MYSQL* getConnection(){return _conn;}

private:
    MYSQL* _conn;
};

// 数据库配置信息
// static string server = "127.0.0.1";
// static string user = "root";
// static string password = "zzong123";
// static string dbname = "chat";
// 数据库操作类
// class MySQL
// {
// public:
//     初始化数据库连接
//     MySQL()
//     {
//         _conn = mysql_init(nullptr);
//     }
//     释放数据库连接资源
//     ~MySQL()
//     {
//         if (_conn != nullptr)
//             mysql_close(_conn);
//     }
//     连接数据库
//     inline bool connect()
//     {
//         MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
//                                       password.c_str(), dbname.c_str(), 3306, nullptr, 0);
//         if (p != nullptr)
//         {
//             LOG_INFO << "数据库连接成功";
//             mysql_query(_conn, "set names gbk");
//         }
//         return p;
//     }
//     更新操作
//     inline bool update(string sql)
//     {
//         if (mysql_query(_conn, sql.c_str()))
//         {
//             LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
//                      << sql << "更新失败!"; 
//             LOG_INFO << "mysql error code: "<< mysql_errno(_conn);

//             return false;
//         }
//         return true;
//     }
//     查询操作
//     inline MYSQL_RES *query(string sql)
//     {
//         if (mysql_query(_conn, sql.c_str()))
//         {
//             LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
//                      << sql << "查询失败!";
//             LOG_INFO << "mysql error code: "<< mysql_errno(_conn);
//             return nullptr;
//         }
//         return mysql_use_result(_conn);
//     }
//     inline MYSQL* getConnection(){return _conn;}

// private:
//     MYSQL *_conn;
// };
