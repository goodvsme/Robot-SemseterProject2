#ifndef CONTROLLER_H
#define CONTROLLER_H
//ALL
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include <QString>

#include "robotur5.h"
#include "gripper.h"
#include "database.h"

class Controller
{
public:
    Controller();
    vector<QString> setup(int test_id);
    void dataUpdate();

    float getAngle(int index);
    void drive(int index, char dir);
    void calibrategripper(int index);
    void setTestID(int id);
    QString getIp(int index);
    QString getComport(int index);
    float getAmp(int index);
    array <float,6> getCords(int index);




private:
    gripper g;
    vector<robotUR5> robots;
    vector<string> gripperports;
    vector<gripper> grippers;

    int test_id;
    bool toggle = 1;

    database d;
};

#endif // CONTROLLER_H
