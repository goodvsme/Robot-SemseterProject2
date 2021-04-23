#include "robotur5.h"

robotUR5::robotUR5()
{
    robotName = "Defult";
    tcpUR5IP = "127.0.0.1";




}

robotUR5::robotUR5(string inN, string inIP)
{
     robotName = inN;
     tcpUR5IP = inIP;




}




bool robotUR5::modbusConnect()
{

        ctx = modbus_new_tcp(tcpUR5IP.c_str(), 502);
        if(modbus_connect(ctx) == -1){

            TCP_Coords = {0,0,0,0,0,0};

            connected = 0;

            return 0;
        }
        int length_of_header = modbus_get_header_length(ctx);


        //reading  registers memory
        read_TCP_Coords = new uint16_t[length_of_header * sizeof(uint16_t) + length_of_TCP_return_values * sizeof(uint16_t)];

        directions = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];
        run = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];
        finished = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];


        finished[0]=0;

        connected = 1;

        return 1;

}

void robotUR5::modbusUpdateCoords()
{
    if(connected){

        //finished
        int bit_write_adress = 142;
        rc = modbus_write_bits(ctx, bit_write_adress, 1, finished);
        if (rc != 1) {
            printf("ERROR modbus_read_bits (%d)\n", rc);
            printf("Address = %d, ADDRESS_START = %d\n", bit_write_adress, 1);
        }

        //Run
        int bit_read_adress_run = 141;
        rc = modbus_read_bits(ctx, bit_read_adress_run, 1, run);
        if (rc != 1) {
            printf("ERROR modbus_read_bits (%d)\n", rc);
            printf("Address = %d, ADDRESS_START = %d\n", bit_read_adress_run, 1);
        }

        //Directions
        int bit_read_adress_direction = 140;
        rc = modbus_read_bits(ctx, bit_read_adress_direction, 1, directions);
        if (rc != 1) {
            printf("ERROR modbus_read_bits (%d)\n", rc);
            printf("Address = %d, ADDRESS_START = %d\n", bit_read_adress_direction, 1);
        }

        //read_TCP_Coords
        int register_read_adress_start = 400; // adress on which the general TCP information is located
        rc = modbus_read_registers(ctx, register_read_adress_start, length_of_TCP_return_values, read_TCP_Coords);
        if (rc != length_of_TCP_return_values) {
            printf("ERROR modbus_read_registers (%d)\n", rc);
            printf("Address = %d, REQUEST_SIZE = %d\n", register_read_adress_start, length_of_TCP_return_values);
        }


        for (int i = 0; i < 6; i++) {
            if (i < 3) {
                if (read_TCP_Coords[i] < 32768){
                    TCP_Coords[i] = ((float) read_TCP_Coords[i])/10.0;
                } else {
                    TCP_Coords[i] = ((float) 65535 - read_TCP_Coords[i])/-10.0;
                }
                if (i == 2){
                    TCP_Coords[i] = TCP_Coords[i] - 400;
                }
            } else {
                if (read_TCP_Coords[i] < 32768){
                    TCP_Coords[i] = ((float) read_TCP_Coords[i])/-1000.0;
                } else {
                    TCP_Coords[i] = ((float) 65535 - read_TCP_Coords[i])/1000.0;
                }
            }
        }



    }
}

void robotUR5::modbusDisconnect()
{

    if(connected){
    modbus_close(ctx);
    modbus_free(ctx);

    delete[] read_TCP_Coords;
    delete[] run;
    delete[] directions;
    delete[] finished;
    }

}

robotUR5::~robotUR5(){
    modbusDisconnect();

}
