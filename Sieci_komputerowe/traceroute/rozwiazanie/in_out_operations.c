#include <stdio.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include "packet_info.h"

bool ip_address_valid(char *ip_addr){
	struct sockaddr_in s;
	int res = inet_pton(AF_INET, ip_addr, &(s.sin_addr));
	return res != 0;
}

bool input_arguments_valid(int argc, char **argv){
	if(argc < 2){
		fprintf(stderr, "Pass ip address as argument\n");
		return false;
	}
	else if(argc > 2){
		fprintf(stderr, "Pass only one argument - the ip address\n");
		return false;
	}
	if(!ip_address_valid(argv[1])){
		fprintf(stderr, "Ip address not valid\n");
		return false;
	}
	return true;
}

void print_time(int* times, bool* received){
	int sum = 0;
	int cnt=0;
	for(int i=0; i<3; i++){
		if(received[i]){
			sum += times[i];
			cnt++;
		}
	}
	if(cnt != 3)
		printf("???\n");
	else
		printf("%dms\n", sum/cnt);
}

void print_ip(u_int32_t ip){
	unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d ",  bytes[0], bytes[1], bytes[2], bytes[3]);
}

void print_routers(u_int32_t* routers, bool* received){
	int cnt = 0;
	u_int32_t printed[3];
	for(int i=0; i<3; i++){
		if(received[i]){
			bool new_router = true;
			for(int j=0; j<cnt; j++){
				if(printed[j] == routers[i])
					new_router = false;
			}
			if(new_router){
				print_ip(routers[i]);
				printed[cnt++] = routers[i];
			}
		}
	}
}

void print_result(struct received_packets *rec_packets, int ttl){
	printf("%d. ", ttl);
	if(rec_packets->packets_received == 0){
		printf("*\n");
	}
	else{
		print_routers(rec_packets->routers, rec_packets->received);
		print_time(rec_packets->times, rec_packets->received);
	}
}
