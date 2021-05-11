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


    gripper g;
    vector<robotUR5> robots;
    vector<string> gripperports;
    vector<gripper> grippers;

    int test_id;
    bool toggle = 1;
private:

    database d;
};

#endif // CONTROLLER_H
