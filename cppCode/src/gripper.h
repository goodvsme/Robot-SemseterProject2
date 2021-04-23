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
    void sendmsg(unsigned char i);
    ~gripper();

    string portCOM;
    unsigned char dataIn [1];


    float amp=0;
    float avg_amp=0;
    float peak_amp=0;
    float force=0;
    float strokeTime=0.05;
    bool direction;
private:
    int serial_port;

    // Allocate memory for read buffer, set size according to your needs




    bool stop = 1;


};

#endif // GRIPPER_H
