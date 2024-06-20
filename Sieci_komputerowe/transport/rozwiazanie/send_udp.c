#include <arpa/inet.h>
#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "sender_window.h"
#include "ip_operations.h"

int min(int a, int b){
    return (a < b) ? a : b;
}

bool send_udp(send_info_t *info, int start, int length){
    int sock_fd = info->sock_fd;
    int port = info->port_number;
    u_int32_t ip_address = info->ip_address;

    struct sockaddr_in receiver;
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(port);
    receiver.sin_addr.s_addr = ip_address;
    socklen_t receiver_len = sizeof(receiver);

    char start_str[10];
    char length_str[6];
    sprintf(start_str, "%d", start);
    sprintf(length_str, "%d", length);

    char message[30];
    strcpy(message, "GET ");
    strcat(message, start_str);
    strcat(message, " ");
    strcat(message, length_str);
    strcat(message, "\n");

    size_t message_len = strlen(message);

    if (sendto(sock_fd, message, message_len, 0, (struct sockaddr*)&receiver, receiver_len) != (ssize_t)message_len) {
        fprintf(stderr, "Sendto error\n");
        return false;
    }
    return true;
}

bool move_window(sender_window_t *window, FILE *file, int *bytes_written){
    segment_t *segments = window->segments;
    for(int i=0; i<window_size; i++){
        int ind = window->first_ind;
        if(segments[ind].ack){
            if(fwrite(segments[ind].buffer, sizeof(int8_t), segments[ind].bytes_number, file) < (size_t)segments[ind].bytes_number){
                fprintf(stderr, "fwrite error\n");
                return false;
            }
            *bytes_written += segments[ind].bytes_number;
            window->lar += 1;
            segments[ind].ack = false;
            segments[ind].send_time.tv_sec = 0;
            window->first_ind = (ind+1)%window_size;
        }
        else
            break;
    }
    return true;
}

bool timeout_reached(segment_t *segment, struct timeval *cur_time){
    if(segment->send_time.tv_sec == 0)
        return true;
    int milisec = (cur_time->tv_sec - segment->send_time.tv_sec) * 1000 + (cur_time->tv_usec - segment->send_time.tv_usec)/1000;
    return milisec >= timeout;
}

int bytes_left(send_info_t *info, sender_window_t *window, int ind){
    return info->file_bytes - (window->lar + ind) * max_bytes;
}

bool send_window(send_info_t *info, sender_window_t *window, FILE *file, int *bytes_written){
    if(!move_window(window, file, bytes_written))
        return false;
    segment_t *segments = window->segments;
    int ind = window->first_ind;
    struct timeval cur_time;
    if(gettimeofday(&cur_time, NULL)<0){
        fprintf(stderr, "gettimeofday error: %s\n", strerror(errno));
        return false;
    }
    int counter = 0;
    for(int i=0; i<window_size; i++){
        if(!segments[ind].ack && timeout_reached(&segments[ind], &cur_time)){
            int bytesLeft = bytes_left(info, window, i);
            if(bytesLeft<=0)
                break;
            for(int j=0; j<number_of_sends; j++)
                if(!send_udp(info, (window->lar + i)*max_bytes, min(max_bytes, bytesLeft)))
                    return false;
            counter += number_of_sends;
            segments[ind].send_time.tv_sec = cur_time.tv_sec;
            segments[ind].send_time.tv_usec = cur_time.tv_usec;
        }
        ind = (ind+1)%window_size;
        if(counter >= 1000)
            break;
    }
    return true;
}
