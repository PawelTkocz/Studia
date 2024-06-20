#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include "packet_info.h"

u_int16_t compute_icmp_checksum (const void *buff, int length){
	const u_int16_t* ptr = buff;
	u_int32_t sum = 0;
	assert (length % 2 == 0);
	for (; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16U) + (sum & 0xffffU);
	return (u_int16_t)(~(sum + (sum >> 16U)));
}

int send_icmp_packet(int sockfd, char *ip_addr, int ttl, u_int16_t id, u_int16_t seq){
	struct icmp header;
	header.icmp_type = ICMP_ECHO;
	header.icmp_code = 0;
	header.icmp_hun.ih_idseq.icd_id = htons(id);
	header.icmp_hun.ih_idseq.icd_seq = htons(seq);
	header.icmp_cksum = 0;
	header.icmp_cksum = compute_icmp_checksum((u_int16_t*)&header, sizeof(header));
	struct sockaddr_in recipient;
	bzero (&recipient, sizeof(recipient));
	recipient.sin_family = AF_INET;
	if(inet_pton(AF_INET, ip_addr, &recipient.sin_addr)<=0){
		fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
		return -1;
	}

	int ttl_value = ttl;
	if(setsockopt (sockfd, IPPROTO_IP, IP_TTL, &ttl_value, sizeof(int)) < 0){
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return -1;
	}

	ssize_t bytes_sent = sendto (sockfd, &header, sizeof(header), 0, (struct sockaddr*)&recipient, sizeof(recipient));
	if(bytes_sent < 0){
		fprintf(stderr, "socket error: %s\n", strerror(errno));
		return -1;
	}
	return 1;
}

int send_packets(struct received_packets *rec_packets, int sock_fd, char *destination_ip_str, int ttl){
	for(int i=0; i<3; i++){
		u_int16_t packet_seq = 3*ttl + i;
		rec_packets->sequences[i] = packet_seq;
		if(send_icmp_packet(sock_fd, destination_ip_str, ttl, rec_packets->packet_id, packet_seq) < 0)
			return -1;
	}
	return 1;
}
