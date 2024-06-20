#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>
#include "get_request.h"
#include "send_response.h"


bool serve_client(int client_sock_fd, int max_connection_time, char *directory){
    int connection_time_left = max_connection_time;
    int req_buff_offset = 0;
    while(connection_time_left > 0){
        RequestParameters_t requestParams;
        int get_request_res = get_request(client_sock_fd, &requestParams, &connection_time_left, &req_buff_offset);
        if(get_request_res < 0)
            return false;
        else if(get_request_res == 0)
            return true;
        else{
            if(!send_response(client_sock_fd, &requestParams, directory))
                return false;
            if(requestParams.bad_request || strcmp(requestParams.connection, "close") == 0)
                return true;
        }
    }
    return true;  
}