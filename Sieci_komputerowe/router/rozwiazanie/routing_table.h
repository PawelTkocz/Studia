#include <stdbool.h>

static const u_int32_t infinity = 0xFFFFFFFF;
static const u_int32_t max_distance = 40;
static const u_int32_t unreachable_max_cnt = 5;
static const u_int32_t silence_max = 5;
static const int round_time = 15000;

typedef struct neighbour_entry{
	u_int32_t my_ip;
	u_int32_t broadcast_address;
	u_int32_t net_address;
	u_int32_t mask;
	u_int32_t distance;
} neighbour_entry_t;

typedef struct udp_data{
	u_int32_t ip;
	u_int8_t mask;
	u_int8_t distance[4];
} udp_data_t;

typedef struct dist_vec_entry{
	u_int32_t ip;
	u_int8_t mask;
	u_int32_t distance;
	u_int32_t predecessor;
	bool neighbour;
	u_int32_t unreachable_send_cnt;
	u_int8_t pred_silence_cnt;
} dist_vec_entry_t;

typedef struct routing_info{
	neighbour_entry_t *neighbours;
	int neigh_cnt;
	dist_vec_entry_t *distance_vector;
	int dist_vec_cnt;
	int dist_vec_max;
} routing_info_t;
