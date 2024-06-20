#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "routing_table.h"
#include "send_udp.h"
#include "receive_udp.h"
#include "in_out_operations.h"
#include "ip_operations.h"

void init_routing_info(routing_info_t *routing_info, dist_vec_entry_t *distance_vector, neighbour_entry_t *neighbours, int n){
	routing_info->distance_vector = distance_vector;
	routing_info->neighbours = neighbours;
	routing_info->dist_vec_cnt = n;
	routing_info->neigh_cnt = n;
	routing_info->dist_vec_max = n;
}

int main()
{
	int neigh_cnt;
	scanf("%d", &neigh_cnt);
	neighbour_entry_t neighbours[neigh_cnt];
	int dist_vec_cnt = neigh_cnt;
	dist_vec_entry_t *distance_vector = malloc(dist_vec_cnt * sizeof(dist_vec_entry_t));
	if(distance_vector == NULL){
		fprintf(stderr, "malloc error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if(!read_and_validate_input(neighbours, distance_vector, neigh_cnt))
		return EXIT_FAILURE;

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}
	int broadcastPermission = 1;
    setsockopt (sock_fd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission));

	struct sockaddr_in router_address;
	memset(&router_address, 0, sizeof(router_address));
	router_address.sin_family = AF_INET;
	router_address.sin_port = htons(54321);
	router_address.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock_fd, (struct sockaddr*)&router_address, sizeof(router_address)) < 0) {
		fprintf(stderr, "bind error: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	routing_info_t routing_info;
	init_routing_info(&routing_info, distance_vector, neighbours, dist_vec_cnt);
	for (;;) {
		if(receive_udp(sock_fd, &routing_info) < 0)
			return EXIT_FAILURE;
		send_routing_table(sock_fd, &routing_info);
		print_routing_table(routing_info.distance_vector, routing_info.dist_vec_cnt);
		fflush(stdout);
	}

	close (sock_fd);
	return EXIT_SUCCESS;
}
