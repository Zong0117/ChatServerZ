#pragma once

#include "group.h"
#include <vector>
#include <string>

class GroupModel
{
public:

    bool createGroup(Group& group);
    void addGroup(int userID, int groupID, std::string role);

    //查询用户所在组信息
    std::vector<Group> queryGroups(int userID);
    /*
      群聊时查找组员分发消息
      先根据userid在group_user中查询出该用户所属的组信息
      再根据群组信息查询属于该群组的所有用户的userid 
      并且和user表联合查询,查到用户的具体信息
    */
    std::vector<int> queryGroupUsers(int userID, int groupID);
};