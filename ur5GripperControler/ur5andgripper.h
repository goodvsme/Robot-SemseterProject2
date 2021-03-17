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

using namespace std;

class ur5AndGripper
{
public:
    ur5AndGripper();


    modbus_t *ctx;


    std::array <float,6> modbusGetCoords();
private:
    int bit_write_adress;
    int bit_read_adress;

    string tcpUR5IP;




};

#endif // UR5ANDGRIPPER_H
