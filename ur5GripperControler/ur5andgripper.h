#ifndef UR5ANDGRIPPER_H
#define UR5ANDGRIPPER_H

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>
#include <array>

#include <mysql.h>

using namespace std;

class ur5AndGripper
{
public:
    ur5AndGripper();
    ur5AndGripper(string RName, string tcpUR5IP, string usbPort, string fName);


    void modbusUpdateCoords();

    string rName;
    string fName;
    string usbPort;
    string tcpUR5IP;

    int ang = 0;

    std::array <float,6> TCP_coords;
private:
    modbus_t *ctx;

    uint16_t *read_registers_memory;
    uint8_t *order;
    uint8_t *directions;
    uint8_t *run;
    uint8_t *finished;







};

#endif // UR5ANDGRIPPER_H
