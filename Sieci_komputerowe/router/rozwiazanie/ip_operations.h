#include <stdlib.h>

u_int32_t ip_address_int(char *ip_addr_str);
bool ip_address_valid(char *ip_addr);
u_int32_t get_broadcast(u_int32_t ip_addr, int mask);
u_int32_t get_net_address(u_int32_t ip_addr, int mask);
bool ip_in_net(u_int32_t ip, u_int32_t net_ip, u_int32_t net_mask);
u_int32_t mark_neighbour_reachable(routing_info_t *routing_info, u_int32_t neigh_ip);
u_int32_t find_neigh_distance(routing_info_t *routing_info, u_int32_t neigh_ip);
