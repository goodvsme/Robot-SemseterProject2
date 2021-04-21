#ifndef GRIPPER_H
#define GRIPPER_H

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
    gripper(string inP);
    bool setAddress(string portCOM);
    void readSerial();
    void closeSerial();

    string portCOM;

private:
    int serial_port;

    // Allocate memory for read buffer, set size according to your needs
    uint8_t read_buf [2];

    //unsigned char msg[]={2};

    bool stop;

    float amp;
    float avg_amp;
    float peak_amp;
    float force;
    float strokeTime;

};

#endif // GRIPPER_H
