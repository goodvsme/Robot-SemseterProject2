#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <string>
#include <vector>
#include "robotur5.h"
#include "gripper.h"

using namespace std;

class database
{
public:
    database();
    vector<robotUR5>getRobots();
    bool setRobot(int index,string newIP);
    vector<gripper>getGrippers();
    bool setGripper(int index,string newCOM);

private:


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    string query;
};

#endif // DATABASE_H
