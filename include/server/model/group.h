#pragma once

#include <string>
#include <vector>

#include "groupuser.h"

class Group
{
public:

    Group(int groupID = -1, std::string groupName = "", std::string groupDesc = "") :
    _groupID(groupID), _groupName(groupName), _groupDesc(groupDesc){}
    void setGroupID(int groupID){_groupID = groupID;}
    void setGroupName(std::string groupName){_groupName = groupName;}
    void setGroupDesc(std::string groupDesc){_groupDesc = groupDesc;}

    int getGroupID(){return _groupID;}
    std::string getGroupName(){return _groupName;}
    std::string getGroupDesc(){return _groupDesc;}
    
    std::vector<GroupUser> getGroupUser(){return _groupUser;}
private:
    int _groupID;
    std::string _groupName;
    std::string _groupDesc;
    std::vector<GroupUser> _groupUser;
};