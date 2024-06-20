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
#include "routing_table.h"
#include "in_out_operations.h"
#include "ip_operations.h"

void mark_predecessor_active(routing_info_t *routing_info, u_int32_t ip){
    int dist_vec_cnt = routing_info->dist_vec_cnt;
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    for(int i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].predecessor == ip)
            distance_vector[i].pred_silence_cnt=0;
    }
}

void mark_predecessors_silent(routing_info_t *routing_info){
    int dist_vec_cnt = routing_info->dist_vec_cnt;
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    for(int i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].distance != infinity && distance_vector[i].predecessor != distance_vector[i].ip)
            distance_vector[i].pred_silence_cnt++;
        else
            distance_vector[i].pred_silence_cnt = 0;
    }
}

int update_routing_table(routing_info_t *routing_info, dist_vec_entry_t *entry){
    mark_predecessor_active(routing_info, entry->predecessor);
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    int dist_vec_cnt = routing_info->dist_vec_cnt;

    u_int32_t pred_dist = find_neigh_distance(routing_info, entry->predecessor);
    if(pred_dist == infinity)
        pred_dist = mark_neighbour_reachable(routing_info, entry->predecessor);

    for(int i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].ip == entry->ip){
            if(distance_vector[i].predecessor == entry->predecessor){
                if(entry->distance == infinity || entry->distance + pred_dist >= max_distance)
                    distance_vector[i].distance = infinity;
                else
                    distance_vector[i].distance = entry->distance + pred_dist;
                return 1;
            }
            break;
        }
    }

    if(entry->distance == infinity || entry->distance + pred_dist >= max_distance)
        return 1;

    u_int32_t new_dist = pred_dist + entry->distance;
    for(int i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].ip == entry->ip && distance_vector[i].mask == entry->mask){
            u_int32_t cur_dist = distance_vector[i].distance;
            if(new_dist < cur_dist){
                distance_vector[i].distance = new_dist;
                distance_vector[i].predecessor = entry->predecessor;
                distance_vector[i].pred_silence_cnt = 0;
            }
            return 1;
        }
    }

    if(routing_info->dist_vec_cnt == routing_info->dist_vec_max){
        routing_info->dist_vec_max *= 2;
        distance_vector = realloc(distance_vector, routing_info->dist_vec_max * sizeof(dist_vec_entry_t));
        routing_info->distance_vector = distance_vector;
        if(!distance_vector){
            fprintf(stderr, "Realloc Error");
            return -1;
        }
    }
    int cur_cnt = routing_info->dist_vec_cnt;
    distance_vector[cur_cnt].ip = entry->ip;
    distance_vector[cur_cnt].distance = new_dist;
    distance_vector[cur_cnt].mask = entry->mask;
    distance_vector[cur_cnt].predecessor = entry->predecessor;
    distance_vector[cur_cnt].pred_silence_cnt = 0;
    distance_vector[cur_cnt].neighbour = false;
    distance_vector[cur_cnt].unreachable_send_cnt = 0;
    routing_info->dist_vec_cnt++;
    return 1;
}

bool self_send_packet(routing_info_t *routing_info, u_int32_t sender_ip){
    u_int32_t neigh_cnt = routing_info->neigh_cnt;
    neighbour_entry_t *neighbours = routing_info->neighbours;
    for(u_int32_t i=0; i<neigh_cnt; i++){
        if(neighbours[i].my_ip == sender_ip)
            return true;
    }
    return false;
}

int receive_udp(int sock_fd, routing_info_t *routing_info){
    mark_predecessors_silent(routing_info);
    struct pollfd ps;
	ps.fd = sock_fd;
	ps.events = POLLIN;
	ps.revents = 0;

	int time_left = round_time;
	struct timeval start, stop;

	while(time_left>0){
        if(gettimeofday(&start, NULL)<0){
            fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));
            return -1;
        }
		int ready = poll(&ps, 1, time_left);
		if(gettimeofday(&stop, NULL)<0){
			fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));
			return -1;
		}
		if(ready == 0)
			break;
		else if (ready < 0){
			fprintf(stderr, "poll error: %s\n", strerror(errno));
			return -1;
		}
        if(ps.revents != POLLIN)
			continue;
        int milisec = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec)/1000;
		time_left -= milisec;

        struct sockaddr_in 	sender;
        socklen_t sender_len = sizeof(sender);
        u_int8_t buffer[IP_MAXPACKET+1];
		while(true){
			errno = 0;
            ssize_t datagram_len = recvfrom(sock_fd, buffer, IP_MAXPACKET, MSG_DONTWAIT, (struct sockaddr*)&sender, &sender_len);
            if(errno==EWOULDBLOCK || errno==EAGAIN)
				break;
            if (datagram_len < 0) {
                fprintf(stderr, "recvfrom error: %s\n", strerror(errno));
                return -1;
            }
            if(self_send_packet(routing_info, sender.sin_addr.s_addr))
                continue;

            dist_vec_entry_t entry;
            udp_data_t *data_ptr = (udp_data_t*)buffer;
            entry.ip = data_ptr->ip;
            entry.mask = data_ptr->mask;
            entry.distance = ntohl(*(u_int32_t*)(data_ptr->distance));
            entry.predecessor = sender.sin_addr.s_addr;
            update_routing_table(routing_info, &entry);
		}
	}
    return 1;
}
