#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>

u_int32_t ip_address_int(char *ip_addr_str){
	struct sockaddr_in s;
	inet_pton(AF_INET, ip_addr_str, &(s.sin_addr));
	return s.sin_addr.s_addr;
}

bool ip_address_valid(char *ip_addr){
	struct sockaddr_in s;
	int res = inet_pton(AF_INET, ip_addr, &(s.sin_addr));
	return res != 0;
}
