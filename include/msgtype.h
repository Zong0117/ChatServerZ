#pragma once

enum MsgType
{
    SUCCESS_NO = 0,  //成功
    FAILD_NO = 999,   //失败

    LOGIN_MSG = 100, //登录
    LOGIN_ACK = 101,  //登录响应

    REGIS_MSG = 200,      //注册
    REGIS_ACK = 201,  //注册响应

    PRI_CHAT_MSG = 300, //一对一聊天
    PRI_CHAT_ACK = 301, //响应

    ADD_FRIEND_MSG = 400,   //添加好友消息
    ADD_FRIEND_ACK = 401,   //响应

    CREATE_GROUP_MSG = 500, //创建群组消息
    CREATE_GROUP_ACK = 501, //创建群组响应

    JOIN_GROUP_MSG = 600, //加入群组消息
    JOIN_GROUP_ACK = 601,   //响应

    SEND_GROUP_MSG = 700,   //群发消息
    SEND_GROUP_ACK = 701,   //响应
};