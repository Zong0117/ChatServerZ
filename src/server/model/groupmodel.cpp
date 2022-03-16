#include "groupmodel.h"
#include "../../include/server/db/db.h"

bool GroupModel::createGroup(Group &group)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into all_group(groupname, groupdesc) value('%s', '%s')",
            group.getGroupName().c_str(), group.getGroupDesc().c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        if(mysql.update(sql))
        {
            group.setGroupID(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}
void GroupModel::addGroup(int userID, int groupID, std::string role)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into group_user(groupid, userid, grouprole) value(%d, %d, '%s')",
            groupID, userID, role.c_str());

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

//查询用户所在组信息
std::vector<Group> GroupModel::queryGroups(int userID)
{
    char sql[1024] = {0};

    //searched is groupid, groupname, groupdesc
    sprintf(sql,"select ag.groupid, ag.groupname, ag.groupdesc from all_group ag \
        inner join group_user gu on ag.groupid = gu.groupid where gu.userid = %d", userID);

    MySQL mysql;
    std::vector<Group> groupInfoVec;

    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            //首先拿到用户所有组的信息
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                Group group;
                group.setGroupID(atoi(row[0]));
                group.setGroupName(row[1]);
                group.setGroupDesc(row[2]);
                groupInfoVec.push_back(group);
            }
            mysql_free_result(res);
        }
        //通过组信息查询到组内所有用户的信息
        for(auto& group : groupInfoVec)
        {
            sprintf(sql,"select u.id, u.name, u.state, gu.grouprole from user u \
                inner join  group_user gu on gu.userid = u.id where gu.groupid = %d",
                    group.getGroupID());
            
            MYSQL_RES* res = mysql.query(sql);
            
            if(res != nullptr)
            {
                MYSQL_ROW row;
                while((row = mysql_fetch_row(res)) != nullptr)
                {
                    GroupUser user;
                    user.setId(atoi(row[0]));
                    user.setName(row[1]);
                    user.setState(row[2]);
                    user.setGroupRole(row[3]);
                    group.getGroupUser().push_back(user);
                }
                mysql_free_result(res);
            }
        }
    } 
    return groupInfoVec;
}
//群聊时查找组员分发消息
std::vector<int> GroupModel::queryGroupUsers(int userID, int groupID)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from group_user where groupid = %d and userid != %d", groupID, userID);

    MySQL mysql;
    std::vector<int> userIdVec;
    
    if(mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);
        if(res != nullptr)
        {
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                userIdVec.push_back(atoi(row[0]));
            }
        }
    }
    return userIdVec;
    
}