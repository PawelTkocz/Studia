#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ip_operations.h"

bool input_arguments_valid(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Give four arguments: IP address, port number, file name and number of bytes\n");
        return false;
    }
    if(!ip_address_valid(argv[1])){
        fprintf(stderr, "IP address not valid\n");
        return false;
    }
    int port_number, file_size;
    sscanf(argv[2], "%d", &port_number);
    sscanf(argv[4], "%d", &file_size);
    if(port_number < 0 || port_number > 65535){
        fprintf(stderr, "Port number not valid\n");
        return false;
    }
    if(file_size < 0 || file_size > 10001000){
        fprintf(stderr, "Number of bytes must be an integer from [0, 10001000]\n");
        return false;
    }
    return true;
}
