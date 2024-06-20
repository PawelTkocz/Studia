#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include "routing_table.h"

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

u_int32_t get_broadcast(u_int32_t ip_addr, int mask){
    u_int32_t ip_host = ntohl(ip_addr);
    u_int32_t bitMask = 0xFFFFFFFF >> mask;
    return htonl(ip_host | bitMask);
}

u_int32_t get_net_address(u_int32_t ip_addr, int mask){
    u_int32_t ip_host = ntohl(ip_addr);
    u_int32_t bitMask = 0xFFFFFFFF << (32-mask);
    return htonl(ip_host & bitMask);
}

bool ip_in_net(u_int32_t ip, u_int32_t net_ip, u_int32_t net_mask){
    u_int32_t host_ip = ntohl(ip);
    return (host_ip > ntohl(net_ip) && host_ip < ntohl(get_broadcast(net_ip, net_mask)));
}

u_int32_t mark_neighbour_reachable(routing_info_t *routing_info, u_int32_t neigh_ip){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    int dist_vec_cnt = routing_info->dist_vec_cnt;
    neighbour_entry_t *neighbours = routing_info->neighbours;
    int neigh_cnt = routing_info->neigh_cnt;
    for(int i=0; i<dist_vec_cnt; i++){
        if(ip_in_net(neigh_ip, distance_vector[i].ip, distance_vector[i].mask)){
            for(int j=0; j<neigh_cnt; j++){
                if(neighbours[j].net_address == distance_vector[i].ip){
                    distance_vector[i].distance = neighbours[j].distance;
                    distance_vector[i].predecessor = distance_vector[i].ip;
                    distance_vector[i].pred_silence_cnt = 0;
                    return distance_vector[i].distance;
                }
            }
        }
    }
    return infinity;
}

u_int32_t find_neigh_distance(routing_info_t *routing_info, u_int32_t neigh_ip){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    int dist_vec_cnt = routing_info->dist_vec_cnt;
    for(int i=0; i<dist_vec_cnt; i++){
        if(ip_in_net(neigh_ip, distance_vector[i].ip, distance_vector[i].mask))
            return distance_vector[i].distance;
    }
    return infinity;
}
