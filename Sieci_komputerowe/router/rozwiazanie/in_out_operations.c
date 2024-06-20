#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include "routing_table.h"
#include "ip_operations.h"

void print_ip(u_int32_t ip, int mask){
	unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
	printf("%d.%d.%d.%d",  bytes[0], bytes[1], bytes[2], bytes[3]);
    if(mask != -1)
        printf("/%d", mask);
}

bool read_and_validate_input(neighbour_entry_t *neighbours, dist_vec_entry_t *distance_vector, int neigh_cnt){
    char ip_with_mask[20];
    char dist_str[20];
    int dist_value;
    for(int i=0; i<neigh_cnt; i++){
        scanf("%s %s %d", ip_with_mask, dist_str, &dist_value);
        int ip_len = strcspn(ip_with_mask, "/");

        if(ip_len == (int)strlen(ip_with_mask)){
            fprintf(stderr, "No subnet mask given\n");
            return false;
        }
        char ip_string[20];
        strncpy(ip_string, ip_with_mask, ip_len);
	    ip_string[ip_len] = '\0';
        if(!ip_address_valid(ip_string)){
            fprintf(stderr, "IP address not valid\n");
            return false;
        }
        char mask[10];
        strcpy(mask, &ip_with_mask[ip_len+1]);
        int mask_value = atoi(mask);
        if(mask_value < 0 || mask_value > 32){
            fprintf(stderr, "Subnet mask not valid\n");
            return false;
        }
        if(strcmp(dist_str, "distance") != 0){
            fprintf(stderr, "Arguments: IP_address 'distance' distance_value\n");
            return false;
        }

        distance_vector[i].ip = get_net_address(ip_address_int(ip_string), mask_value);
        distance_vector[i].distance = dist_value;
        distance_vector[i].mask = mask_value;
        distance_vector[i].predecessor = distance_vector[i].ip;
        distance_vector[i].neighbour = true;
        distance_vector[i].unreachable_send_cnt = 0;
        distance_vector[i].pred_silence_cnt = 0;

        neighbours[i].broadcast_address = get_broadcast(ip_address_int(ip_string), mask_value);
        neighbours[i].net_address = get_net_address(ip_address_int(ip_string), mask_value);
        neighbours[i].distance = dist_value;
        neighbours[i].mask = mask_value;
        neighbours[i].my_ip = ip_address_int(ip_string);
    }
    return true;
}

void print_routing_table(dist_vec_entry_t *distance_vector, int dist_vec_cnt){
    printf("\n");
    for(int i=0; i<dist_vec_cnt; i++){
        dist_vec_entry_t entry = distance_vector[i];
        print_ip(entry.ip, entry.mask);

        if(entry.distance == infinity){
            printf(" unreachable");
            if(entry.neighbour)
                printf(" connected directly");
        }
        else{
            printf(" distance %d ", entry.distance);
            if(entry.predecessor == entry.ip)
                printf("connected directly");
            else{
                printf("via ");
                print_ip(entry.predecessor, -1);
            }
        }
        printf("\n");
    }
}
