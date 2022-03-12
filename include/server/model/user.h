#pragma once

#include <string>
//user表的映射类
class User
{
public:
    User() : _id(-1), _name(""), _password(""), _state("offline") {}

    void setId(int id) { _id = id; }
    void setName(const std::string name) { _name = name; }
    void setPassword(const std::string password) { _password = password; }
    void setState(const std::string state) { _state = state; }

    int getId() { return this->_id; }
    std::string getName() { return this->_name; }
    std::string getPassword() { return this->_password; }
    std::string getState() { return this->_state; }

protected:
    int _id;
    std::string _name;
    std::string _password;
    std::string _state;
};
