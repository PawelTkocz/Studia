#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "routing_table.h"
#include "in_out_operations.h"
#include "ip_operations.h"

void mark_neigh_unreachable(routing_info_t *routing_info, u_int32_t ip_neigh_net, u_int32_t neigh_mask){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    u_int32_t dist_vec_cnt = routing_info->dist_vec_cnt;
    for(u_int32_t i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].ip == ip_neigh_net && distance_vector[i].predecessor == distance_vector[i].ip)
            distance_vector[i].distance = infinity;
        else if(ip_in_net(distance_vector[i].predecessor, ip_neigh_net, neigh_mask))
            distance_vector[i].distance = infinity;
    }
}

int send_udp(int sock_fd, routing_info_t *routing_info, neighbour_entry_t *neighbour, dist_vec_entry_t *entry){
    u_int32_t broadcast = neighbour->broadcast_address;
    struct sockaddr_in sender;
    sender.sin_family = AF_INET;
    sender.sin_port = htons(54321);
    sender.sin_addr.s_addr = broadcast;
    socklen_t sender_len = sizeof(sender);
    udp_data_t data;
    data.ip = entry->ip;
    data.mask = entry->mask;
    u_int32_t *dist_ptr = (u_int32_t *)&data.distance;
    *dist_ptr = htonl(entry->distance);
    size_t data_len = 9;

    if (sendto(sock_fd, &data, data_len, 0, (struct sockaddr*)&sender, sender_len) != (ssize_t)data_len) {
        mark_neigh_unreachable(routing_info, neighbour->net_address, neighbour->mask);
        return -1;
    }
    else if(find_neigh_distance(routing_info, neighbour->my_ip) == infinity){
        mark_neighbour_reachable(routing_info, neighbour->my_ip);
    }
    return 1;
}

void check_inactive_predecessors(routing_info_t *routing_info){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    int dist_vec_cnt = routing_info->dist_vec_cnt;
    for(int i=0; i<dist_vec_cnt; i++){
        if(distance_vector[i].pred_silence_cnt >= silence_max && distance_vector[i].predecessor != distance_vector[i].ip){
            distance_vector[i].pred_silence_cnt = 0;
            distance_vector[i].distance = infinity;
        }
    }
}

void remove_net(routing_info_t *routing_info, int ind){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    u_int32_t dist_vec_cnt = routing_info->dist_vec_cnt;

    distance_vector[ind].ip = distance_vector[dist_vec_cnt-1].ip;
    distance_vector[ind].mask = distance_vector[dist_vec_cnt-1].mask;
    distance_vector[ind].distance = distance_vector[dist_vec_cnt-1].distance;
    distance_vector[ind].neighbour = distance_vector[dist_vec_cnt-1].neighbour;
    distance_vector[ind].predecessor = distance_vector[dist_vec_cnt-1].predecessor;
    distance_vector[ind].unreachable_send_cnt = distance_vector[dist_vec_cnt-1].unreachable_send_cnt;
    distance_vector[ind].pred_silence_cnt = distance_vector[dist_vec_cnt-1].pred_silence_cnt;
    routing_info->dist_vec_cnt--;
}

void remove_unreachable_nets(routing_info_t *routing_info){
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;
    uint32_t dist_vec_cnt = routing_info->dist_vec_cnt;
    for(uint32_t i = 0; i<dist_vec_cnt; i++){
        if(distance_vector[i].distance == infinity){
            distance_vector[i].unreachable_send_cnt++;
            if(distance_vector[i].unreachable_send_cnt > unreachable_max_cnt && !distance_vector[i].neighbour){
                remove_net(routing_info, i);
                i--;
                dist_vec_cnt--;
            }
        }
        else
            distance_vector[i].unreachable_send_cnt = 0;
    }
}

void send_routing_table(int sock_fd, routing_info_t *routing_info){
    int neigh_cnt = routing_info->neigh_cnt;
    neighbour_entry_t *neighbours = routing_info->neighbours;
    dist_vec_entry_t *distance_vector = routing_info->distance_vector;

    check_inactive_predecessors(routing_info);
    remove_unreachable_nets(routing_info);

    int dist_vec_cnt = routing_info->dist_vec_cnt;
    for(int i=0; i<neigh_cnt; i++){
        for(int j=0; j<dist_vec_cnt; j++){
            if(distance_vector[j].unreachable_send_cnt >= unreachable_max_cnt)
                continue;
            if(send_udp(sock_fd, routing_info, &neighbours[i], &distance_vector[j]) < 0)
                break;
        }
    }
}
