#ifndef GRIPPER_H
#define GRIPPER_H
#include "database.h"
#include "robotur5.h"

//general includes
#include <iostream>
#include <string.h>
#include <errno.h>
#include <stdio.h>

//specific includes
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <termios.h>

using namespace std;

class gripper
{
public:
    gripper();
    bool setAddress(string portCOM);
    bool readSerial(class database *inwrite, int testid, int rAgID);
    void closeSerial();
    void sendmsg(unsigned char i);
    ~gripper();

    string portCOM;
    unsigned char dataIn[1] = {128};


    float amp=0;
    float avg_amp=0;
    float peak_amp=0;
    float force=0;
    float strokeTime=0;
    int direction = 0;
    float angleTime = 0;
    float angle = 0;

    const float speed = 26;
private:
    int serial_port;

    bool stop = 1;


};

#endif // GRIPPER_H
