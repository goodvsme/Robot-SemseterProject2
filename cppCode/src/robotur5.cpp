#include "robotur5.h"

robotUR5::robotUR5()
{

}

robotUR5::robotUR5(string inN, string inIP, string inUSB)
{
     robotName = inN;
     tcpUR5IP = inIP;
     usbPort = inUSB;
}

void robotUR5::modbusUpdateCoords()
{

}
