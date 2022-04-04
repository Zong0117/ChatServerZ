#pragma once

#include <string>
//user表的映射类
class User
{
public:
    User(int id = -1, std::string name = " ", std::string password = "", std::string state = "offline") 
        :_id(id), _name(name), _password(password), _state(state){}

    void setId(int id) {_id = id; }
    void setName(std::string name) {_name = name; }
    void setPassword(std::string password) { _password = password; }
    void setState(std::string state) { _state = state; }

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
