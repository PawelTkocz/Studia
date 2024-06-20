#include <sys/time.h>
#include <stdbool.h>
#include <netinet/ip.h>
#include <stdlib.h>

static const int window_size = 1000;

typedef struct segment{
    bool ack;
    struct timeval send_time;
    u_int8_t buffer[1000];
    int bytes_number;
} segment_t;

typedef struct sender_window{
	int lar;
    segment_t *segments;
    int first_ind;
} sender_window_t;

typedef struct send_info{
    int sock_fd;
    int port_number;
    u_int32_t ip_address;
    int file_bytes;
    int bytes_read;
} send_info_t;

void init_sender_window(sender_window_t *window, segment_t *segments){
    window->lar = 0;
    window->segments = segments;
    window->first_ind = 0;
    for(int i=0; i<window_size; i++){
        segments[i].ack = false;
        segments[i].send_time.tv_sec = 0;
        segments[i].send_time.tv_usec = 0;
    }
}

void init_send_info(send_info_t *info, int sock_fd, int port, u_int32_t ip_address, int file_bytes){
    info->sock_fd = sock_fd;
    info->port_number = port;
    info->ip_address = ip_address;
    info->file_bytes = file_bytes;
    info->bytes_read = 0;
}
