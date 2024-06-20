#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "receive_packet.h"
#include "send_packet.h"
#include "in_out_operations.h"

u_int32_t ip_address_int(char *ip_addr_str){
	struct sockaddr_in s;
	inet_pton(AF_INET, ip_addr_str, &(s.sin_addr));
	return s.sin_addr.s_addr;
}

void init_received_packets(struct received_packets *rec_packets){
	pid_t pid = getpid();
	u_int16_t packet_id = pid & 0xffff;
	rec_packets->packet_id = packet_id;
}

int main(int argc, char **argv){

	if(!input_arguments_valid(argc, argv))
		return EXIT_FAILURE;

	char *destination_ip_str = argv[1];
	u_int32_t destination_ip = ip_address_int(destination_ip_str);

	int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock_fd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	struct received_packets rec_packets;
	init_received_packets(&rec_packets);

	int finished = 0;
	for(int ttl=1; ttl<=30; ttl++){
		if(send_packets(&rec_packets, sock_fd, destination_ip_str, ttl) < 0)
			return EXIT_FAILURE;
		finished = receive_packets(&rec_packets, sock_fd, destination_ip);
		if(finished < 0)
			return EXIT_FAILURE;
		print_result(&rec_packets, ttl);
		if(finished == 1)
			break;
	}

	return 0;
}
