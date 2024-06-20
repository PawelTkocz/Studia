#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct RequestParameters{
    char requested_path[200];
    char host[100];
    char connection[100];
    bool bad_request;
} RequestParameters_t;

int get_request(int fd, RequestParameters_t *requestParameters, int *max_waiting_time, int *buffer_offset);