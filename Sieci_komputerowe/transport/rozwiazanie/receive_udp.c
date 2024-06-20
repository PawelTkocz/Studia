#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>
#include <sys/time.h>
#include <stdbool.h>
#include "in_out_operations.h"
#include "ip_operations.h"
#include "sender_window.h"

u_int8_t* read_udp_header(int *start, int *length, u_int8_t *buffer){
    const int asci_space = 32;
    const int asci_new_line = 10;
    int s = 0;
    int l = 0;
    int ind = 5;

    for(; buffer[ind] != asci_space; ind++)
        s = 10*s + buffer[ind] - '0';
    ind++;
    for(; buffer[ind] != asci_new_line; ind++)
        l = 10*l + buffer[ind] - '0';

    *start = s;
    *length = l;
    return &buffer[ind+1];
}

bool correct_udp(send_info_t *info, u_int32_t ip_address, int port_number){
    return info->ip_address == ip_address && info->port_number == port_number;
}

int get_window_ind(sender_window_t *window, int start){
    if(start%max_bytes != 0)
        return -1;
    start /= max_bytes;
    if(window->lar > start || window->lar + window_size <= start)
        return -1;
    return start - window->lar;
}

void copy_buffer(u_int8_t *source, u_int8_t *dest, int len){
    for(int i=0; i<len; i++)
        dest[i] = source[i];
}

bool receive_udp(send_info_t *info, sender_window_t *window){
    struct pollfd ps;
	ps.fd = info->sock_fd;
	ps.events = POLLIN;
	ps.revents = 0;
	while(true){
		int ready = poll(&ps, 1, 0);
		if (ready < 0){
			fprintf(stderr, "poll error: %s\n", strerror(errno));
			return false;
		}
        if(ready == 0){
            return true;
        }
        if(ps.revents != POLLIN)
			continue;

        struct sockaddr_in 	sender;
        socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET+1];
		while(true){
			errno = 0;
            ssize_t datagram_len = recvfrom(info->sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
            if(errno==EWOULDBLOCK || errno==EAGAIN)
				break;
            if (datagram_len < 0) {
                fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
                return false;
            }
            if(!correct_udp(info, sender.sin_addr.s_addr, ntohs(sender.sin_port)))
                continue;

            int start, length;
            u_int8_t *file_bytes = read_udp_header(&start, &length, buffer);

            int ind = get_window_ind(window, start);
            if(ind < 0)
                continue;

            int first_ind = window->first_ind;
            if(window->segments[(first_ind+ind) % window_size].ack)
                continue;

            int seg_ind = (first_ind+ind) % window_size;
            window->segments[seg_ind].ack = true;
            window->segments[seg_ind].bytes_number = length;
            copy_buffer(file_bytes, window->segments[seg_ind].buffer, length);
            info->bytes_read += length;
            float percentage = (double)info->bytes_read / info->file_bytes * 100;
            printf("%.2f%% done\n", percentage);
		}
	}
    return true;
}
