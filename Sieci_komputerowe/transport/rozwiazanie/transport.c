#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sender_window.h"
#include "send_udp.h"
#include "receive_udp.h"
#include "in_out_operations.h"
#include "ip_operations.h"

int main(int argc, char **argv)
{
    if(!input_arguments_valid(argc, argv))
		return EXIT_FAILURE;

    u_int32_t ip_address = ip_address_int(argv[1]);
    int port;
	sscanf(argv[2], "%d", &port);
    char *fileName = argv[3];
    int fileSize;
	sscanf(argv[4], "%d", &fileSize);

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

    FILE *file = fopen(fileName, "w");
    if(!file){
        fprintf(stderr, "Failed to open file\n");
        return EXIT_FAILURE;
    }

	sender_window_t window;
	segment_t segments[window_size];
	init_sender_window(&window, segments);

	send_info_t send_info;
	init_send_info(&send_info, sock_fd, port, ip_address, fileSize);

	int bytes_written = 0;
	while(bytes_written != fileSize){
		if(!send_window(&send_info, &window, file, &bytes_written))
			return EXIT_FAILURE;
		if(!receive_udp(&send_info, &window))
			return EXIT_FAILURE;
	}

    fclose(file);
	close (sock_fd);
	return EXIT_SUCCESS;
}
