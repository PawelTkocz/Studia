#include <sys/time.h>
#include <stdbool.h>

static const int window_size = 1000;
static const int timeout = 1000;
static const int max_bytes = 1000;
static const int number_of_sends = 5;

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

void init_sender_window(sender_window_t *window, segment_t *segments);
void init_send_info(send_info_t *info, int sock_fd, int port, u_int32_t ip_address, int file_bytes);
