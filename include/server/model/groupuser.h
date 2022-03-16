#pragma once

#include "user.h"
#include <string>
class GroupUser : public User
{
public:
    void setGroupRole(std::string role){_groupRole = role;};
    std::string getGroupRole(){return _groupRole;};
private:
    std::string _groupRole;
};