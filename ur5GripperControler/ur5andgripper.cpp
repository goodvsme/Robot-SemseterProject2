#include "ur5andgripper.h"

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

#include <mysql.h>

#include <array>
#include <iostream>


ur5AndGripper::ur5AndGripper()
{

}

ur5AndGripper::ur5AndGripper(string inR, string inIP, string inUSB, string inF)
{
     rName = inR;
     tcpUR5IP = inIP;
     usbPort = inUSB;
     fName = inF;
}

void ur5AndGripper::modbusUpdateCoords(){

    int rc;

    /* TCP */
    ctx = modbus_new_tcp(tcpUR5IP.c_str(), 502);

    if (modbus_connect(ctx) == -1) {     
        modbus_free(ctx);
        TCP_coords = {0,0,0,0,0,0};

    }else{
        int length_of_TCP_return_values = 6; // The amount of values returned from later register reads
        int length_of_header = modbus_get_header_length(ctx); //
        //reading  registers memory
        read_registers_memory  = new  uint16_t[length_of_header * sizeof(uint16_t) + length_of_TCP_return_values * sizeof(uint16_t)];

        //Reading bits
        order = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];
        directions = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];
        run = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];

        //Writing bits
        finished = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];




        finished[0] = 0;


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
        printf("Bit: %i\n", run[0]);

        //Directions
        int bit_read_adress_direction = 140;
        rc = modbus_read_bits(ctx, bit_read_adress_direction, 1, directions);
        if (rc != 1) {
            printf("ERROR modbus_read_bits (%d)\n", rc);
            printf("Address = %d, ADDRESS_START = %d\n", bit_read_adress_direction, 1);
        }
        printf("Bit: %i\n", directions[0]);


        //Order
        int bit_read_adress_order = 140;
        rc = modbus_read_bits(ctx, bit_read_adress_order, 1, order);
        if (rc != 1) {
            printf("ERROR modbus_read_bits (%d)\n", rc);
            printf("Address = %d, ADDRESS_START = %d\n", bit_read_adress_order, 1);
        }
        printf("Bit: %i\n", order[0]);







        int register_read_adress_start = 400; // adress on which the general TCP information is located
        rc = modbus_read_registers(ctx, register_read_adress_start, length_of_TCP_return_values, read_registers_memory);
        if (rc != length_of_TCP_return_values) {
            printf("ERROR modbus_read_registers (%d)\n", rc);
            printf("Address = %d, REQUEST_SIZE = %d\n", register_read_adress_start, length_of_TCP_return_values);
        }

        for (int i = 0; i < 6; i++) {
            if (i < 3) {
                if (read_registers_memory[i] < 32768){
                    TCP_coords[i] = ((float) read_registers_memory[i])/10.0;
                } else {
                    TCP_coords[i] = ((float) 65535 - read_registers_memory[i])/-10.0;
                }
                if (i == 2){
                    TCP_coords[i] = TCP_coords[i] - 400;
                }
            } else {
                if (read_registers_memory[i] < 32768){
                    TCP_coords[i] = ((float) read_registers_memory[i])/-1000.0;
                } else {
                    TCP_coords[i] = ((float) 65535 - read_registers_memory[i])/1000.0;
                }
            }
        }

        delete[] read_registers_memory;
        delete[] order;
        delete[] run;
        delete[] directions;
        delete[] finished;


        /* Close the connection */
        modbus_close(ctx);
        modbus_free(ctx);
    }



}
