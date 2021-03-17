#include "ur5andgripper.h"

#ifndef _MSC_VER
#include <unistd.h>
#endif

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

#include <array>
#include <iostream>

ur5AndGripper::ur5AndGripper()
{

}

std::array <float,6> ur5AndGripper::modbusGetCoords(){



    int rc;
    uint16_t *read_registers_memory;
    uint8_t *read_bits_memory;
    uint8_t *write_bits_memory;


    /* TCP */
    ctx = modbus_new_tcp("127.0.0.1", 502);

    if (modbus_connect(ctx) == -1) {
        std::cout << stderr << "Connection failed: %s\n" << modbus_strerror(errno);
        modbus_free(ctx);
        std::cout << -1;
    }


    int length_of_TCP_return_values = 6; // The amount of values returned from later register reads
    int length_of_header = modbus_get_header_length(ctx); //
    //reading  registers memory
    read_registers_memory  = new  uint16_t[length_of_header * sizeof(uint16_t) + length_of_TCP_return_values * sizeof(uint16_t)];

    //Reading bits
    read_bits_memory = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];

    //Writing bits
    write_bits_memory = new uint8_t [(length_of_header * sizeof(uint8_t) + 1 * sizeof(uint8_t))];



    int register_read_adress_start = 400; // adress on which the general TCP information is located
    rc = modbus_read_registers(ctx, register_read_adress_start, length_of_TCP_return_values, read_registers_memory);
    if (rc != length_of_TCP_return_values) {
        printf("ERROR modbus_read_registers (%d)\n", rc);
        printf("Address = %d, REQUEST_SIZE = %d\n", register_read_adress_start, length_of_TCP_return_values);
    }


    std::array <float , 6> TCP_coords;
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
    delete[] read_bits_memory;
    delete[] write_bits_memory;

    /* Close the connection */
    modbus_close(ctx);
    modbus_free(ctx);



    return TCP_coords;

}
