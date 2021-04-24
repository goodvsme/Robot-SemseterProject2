#ifndef ROBOTUR5_H
#define ROBOTUR5_H

#include <modbus.h>
#include <string>
#include <array>
#include <iostream>

using namespace std;

class robotUR5
{
public:
    robotUR5();
    robotUR5(string robotName, string tcpUR5IP);
    void modbusUpdateCoords();
    bool modbusConnect();
    void modbusDisconnect();

    ~robotUR5();

    array <float,6> TCP_Coords;

    string robotName;
    string tcpUR5IP;
private:
    bool connected = 0;





    //Modbus
    int rc;

    modbus_t *ctx;

    int length_of_TCP_return_values = 6; // The amount of values returned from later register reads

    uint16_t *read_TCP_Coords;
    uint8_t *directions;
    uint8_t *run;
    uint8_t *finished;
};

#endif // ROBOTUR5_H
