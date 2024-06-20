#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>

typedef struct RequestParameters{
    char requested_path[200];
    char host[100];
    char connection[100];
    bool bad_request;
} RequestParameters_t;

#define BUFFER_SIZE 10000000 // 10 MB
u_int8_t http_request[BUFFER_SIZE+1];
char newLineSequence[2] = "\r\n"; 

void copy_buffer_string(u_int8_t *buf, int len, char *dest){
    uint8_t temp = buf[len];
    buf[len] = '\0';
    memcpy(dest, (char*)buf, len+1);
    buf[len] = temp;
}

bool compare_buffer_string(uint8_t *buf, char *str){
    int str_len = strlen(str);
    uint8_t temp = buf[str_len];
    buf[str_len] = '\0';
    int res = strcmp((char*)buf, str);
    buf[str_len] = temp;
    return res == 0;
}

bool get_requested_path(RequestParameters_t *requestParams){
    char get_string[] = "GET /";
    if(!compare_buffer_string(http_request, get_string))
        return false;
    char *requested_path = (char*)&http_request[strlen(get_string)];
    char *space = strchr(requested_path, ' ');
    char *newLine = strstr(requested_path, newLineSequence);
    if(space == NULL || space > newLine)
        return false;
    char rest_of_line[50];
    strcpy(rest_of_line, " HTTP/1.1");
    strcat(rest_of_line, newLineSequence);
    if(!compare_buffer_string((uint8_t*)space, rest_of_line))
        return false;
    copy_buffer_string((uint8_t*)requested_path, space-requested_path, requestParams->requested_path);
    return true;
}

bool get_host(char *request_end, RequestParameters_t *requestParams){
    char host_string[] = "\nHost: ";
    char *host_string_pos = strstr((char*)http_request, host_string);
    if(host_string_pos == NULL || host_string_pos > request_end)
        return false;

    char *host = &host_string_pos[strlen(host_string)];
    char *space = strchr(host, ' ');
    char *newLine = strstr(host, newLineSequence);
    if(space != NULL && space < newLine)
        return false;

    copy_buffer_string((uint8_t*)host, newLine-host, requestParams->host);
    return true;
}

bool get_connection_state(char *request_end, RequestParameters_t *requestParams){
    char connection_string[] = "\nConnection: ";
    char *connection_string_pos = strstr((char*)http_request, connection_string);
    if(connection_string_pos == NULL || connection_string_pos > request_end)
        return false;

    char *connection = &connection_string_pos[strlen(connection_string)];
    char *space = strchr(connection, ' ');
    char *newLine = strstr(connection, newLineSequence);
    if(space != NULL && space < newLine)
        return false;

    copy_buffer_string((uint8_t*)connection, newLine-connection, requestParams->connection);
    return true;
}

bool fillRequestParams(RequestParameters_t *requestParams, u_int8_t *request_end){
    if(!get_requested_path(requestParams))
        return false;
    if(!get_host((char*)request_end, requestParams))
        return false;
    if(!get_connection_state((char*)request_end, requestParams))
        strcpy(requestParams->connection, "keep-alive");
    return true;
}

int request_ready(int bytes_read, RequestParameters_t *requestParameters, int *buffer_offset){
    http_request[bytes_read] = '\0';
    char double_new_line[20];
    strcpy(double_new_line, newLineSequence);
    strcat(double_new_line, newLineSequence);
    char *request_end = strstr((char*)http_request, double_new_line);
    if(request_end == NULL)
        return 0;
    
    if(fillRequestParams(requestParameters, (uint8_t*)request_end)){
        int request_len = (request_end-(char*)http_request) + strlen(double_new_line);
        memmove(http_request, &request_end[strlen(double_new_line)], bytes_read - request_len);
        *buffer_offset = bytes_read - request_len;
        return 1;
    }
    return -1;
}

int time_poll(int fd, int *max_waiting_time){
    struct timeval clock_before, clock_after, time_elapsed;
    struct pollfd ps;

    gettimeofday(&clock_before, NULL);
    ps.fd = fd;
    ps.events = POLLIN;
    ps.revents = 0;
    int ready = poll(&ps, 1, *max_waiting_time);
    if(ready < 0 || (ready > 0 && ps.revents != POLLIN)){
        fprintf(stderr, "Poll error\n");
        return -1;
    }
    if(ready == 0) {
        *max_waiting_time = 0;
        return 0;
    }

    gettimeofday(&clock_after, NULL);
    timersub(&clock_after, &clock_before, &time_elapsed);
    *max_waiting_time -= (int)(time_elapsed.tv_sec * 1000 + time_elapsed.tv_usec / 1000);
    if (*max_waiting_time < 0)
        *max_waiting_time = 0;

    return 1;
}

int get_request(int fd, RequestParameters_t *requestParameters, int *max_waiting_time, int *buffer_offset){
    requestParameters->bad_request = false;
    int total_bytes_read = *buffer_offset;
    while(total_bytes_read < BUFFER_SIZE){
        int request_state = request_ready(total_bytes_read, requestParameters, buffer_offset);
        if(request_state < 0){
            requestParameters->bad_request = true;
            *buffer_offset = 0;
            return 1;
        }
        else if(request_state > 0)
            return 1;

        int time_poll_ret = time_poll(fd, max_waiting_time);
        if(time_poll_ret < 0)
            return -1;
        if(time_poll_ret == 0){
            if(total_bytes_read == 0)
                return 0;
            else{
                requestParameters->bad_request = true;
                *buffer_offset = 0;
                return 1;
            }
        }

        int bytes_read = recv(fd, http_request + total_bytes_read, BUFFER_SIZE - total_bytes_read, 0);
        if(bytes_read < 0){
            fprintf(stderr, "Recv error\n");
            return -1;
        }
        if(bytes_read == 0){
            *buffer_offset = 0;
            return 0;
        }
        total_bytes_read += bytes_read;
    }
    *buffer_offset = 0;
    requestParameters->bad_request = true;
    return 1;
}