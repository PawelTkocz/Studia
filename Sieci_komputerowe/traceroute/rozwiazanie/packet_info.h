struct packet_info{
    u_int8_t ip_protocol;
    u_int32_t ip_src;
    u_int32_t ip_dst;
    u_int8_t icmp_type;
    u_int8_t icmp_code;
    u_int16_t icmp_id_num;
    u_int16_t icmp_seq_num;
    u_int16_t icmp_checksum;
};

struct received_packets{
    int packets_received;
    bool received[3];
    u_int32_t routers[3];
    int times[3];
    u_int16_t sequences[3];
    u_int16_t packet_id;
};
