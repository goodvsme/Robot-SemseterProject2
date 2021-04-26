#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <string>
#include <vector>
#include "robotur5.h"
#include "gripper.h"
#include <sstream>

using namespace std;

class database
{
public:
    database();
    vector<robotUR5>getRobots();
    vector<string>getGrippers();
    void sendData(int test,int rAg, double ampP, double ampA, int stroke, double force, double time, bool dir);

private:


    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    string query;
    const char* q;
    int qstate;
    vector<robotUR5> ur5Bots;
    vector<string> gripperports;
};

#endif // DATABASE_H
