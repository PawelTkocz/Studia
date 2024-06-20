#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/ip_icmp.h>
#include <poll.h>
#include <sys/time.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "packet_info.h"

void get_packet_info(u_int8_t *buffer, struct packet_info* packet_info){
	struct ip* ip_header = (struct ip*) buffer;
	ssize_t	ip_header_len = 4 * (ssize_t)(ip_header->ip_hl);

	packet_info->ip_protocol = ip_header->ip_p;
	packet_info->ip_src = ip_header->ip_src.s_addr;
	packet_info->ip_dst = ip_header->ip_dst.s_addr;

	struct icmp *icmp_header = (struct icmp*)(buffer+ip_header_len);
	packet_info->icmp_type = icmp_header->icmp_type;
	packet_info->icmp_code = icmp_header->icmp_code;
	packet_info->icmp_checksum = icmp_header->icmp_cksum;
	if(packet_info->icmp_type == 11){
		ssize_t inside_ip_offset = ip_header_len + 8;
		struct ip* inside_ip_header = (struct ip*)(buffer+inside_ip_offset);
		ssize_t inside_ip_header_len = 4 * (ssize_t)(inside_ip_header->ip_hl);
		struct icmp *inside_icmp_header = (struct icmp*)(buffer+inside_ip_offset+inside_ip_header_len);
		packet_info->icmp_id_num = ntohs(inside_icmp_header->icmp_hun.ih_idseq.icd_id);
		packet_info->icmp_seq_num = ntohs(inside_icmp_header->icmp_hun.ih_idseq.icd_seq);
	}
	else{
		packet_info->icmp_id_num = ntohs(icmp_header->icmp_hun.ih_idseq.icd_id);
		packet_info->icmp_seq_num = ntohs(icmp_header->icmp_hun.ih_idseq.icd_seq);
	}
}

int verify_packet(struct packet_info* p, u_int16_t id, u_int16_t* sequences){
	if(p->ip_protocol != 1)
		return -1;

	if(p->icmp_id_num != id)
		return -1;

	u_int16_t seq = p->icmp_seq_num;
	for(int i=0; i<3; i++){
		if(sequences[i] == seq)
			return i;
	}
	return -1;
}

int receive_packets(struct received_packets *rec_packets, int sock_fd, u_int32_t destination_ip){
	rec_packets->received[0] = false;
	rec_packets->received[1] = false;
	rec_packets->received[2] = false;
	rec_packets->packets_received = 0;

	struct pollfd ps;
	ps.fd = sock_fd;
	ps.events = POLLIN;
	ps.revents = 0;

	int time_left = 1000;
	struct timeval start, stop;
	bool finished = 0;
	while(true){
		if(gettimeofday(&start, NULL)<0){
			fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));
			return -1;
		}
		int ready = poll(&ps, 1, time_left);
		if(gettimeofday(&stop, NULL)<0){
			fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));
			return -1;
		}
		int milisec = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec)/1000;
		time_left -= milisec;
		if(ready == 0)
			return finished;
		else if (ready < 0){
			fprintf(stderr, "poll error: %s\n", strerror(errno));
			return -1;
		}
		if(ps.revents != POLLIN)
			continue;
		struct sockaddr_in sender;
		socklen_t sender_len = sizeof(sender);
		u_int8_t buffer[IP_MAXPACKET];
		while(true){
			errno = 0;
			ssize_t packet_len = recvfrom (sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
			if(errno==EWOULDBLOCK || errno==EAGAIN)
				break;

			if (packet_len < 0) {
				fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
				return -1;
			}
			struct packet_info pckt_info;
			get_packet_info(buffer, &pckt_info);
			int packet_num = verify_packet(&pckt_info, rec_packets->packet_id, rec_packets->sequences);
			if(packet_num<0)
				continue;
			if(pckt_info.ip_src == destination_ip){
				finished = 1;
			}
			if(!rec_packets->received[packet_num]){
				rec_packets->times[packet_num] = 1000-time_left;
				rec_packets->routers[packet_num] = pckt_info.ip_src;
				rec_packets->received[packet_num] = true;
				rec_packets->packets_received++;
			}
		}
		if(rec_packets->packets_received == 3)
			return finished;
	}
}
