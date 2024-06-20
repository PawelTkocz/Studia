#include <stdbool.h>

bool read_and_validate_input(neighbour_entry_t *neighbours, dist_vec_entry_t *distance_vector, int neigh_cnt);
void print_routing_table(dist_vec_entry_t *distance_vector, int dist_vec_cnt);
