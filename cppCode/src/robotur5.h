#ifndef ROBOTUR5_H
#define ROBOTUR5_H

#include "widget.h"
#include <modbus.h>

using namespace std;

class robotUR5
{
public:
    robotUR5();
    robotUR5(string robotName, string tcpUR5IP, string usbPort);
    void modbusUpdateCoords();
private:
    string robotName;
    string tcpUR5IP;
    string usbPort;

    //Modbus
    int rc;

    modbus_t *ctx;

    shared_ptr<uint16_t> read_registers_memory;
    shared_ptr<uint8_t> directions;
    shared_ptr<uint8_t> run;
};

#endif // ROBOTUR5_H
