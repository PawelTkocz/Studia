#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include "serve_client.h"

#define CONNECTION_MAX_TIME 400

bool input_arguments_valid(int argc, char **argv){
    if(argc != 3){
        fprintf(stderr, "Give two arguments: port number and directory with WWW pages\n");
        return false;
    }
    int port_number;
    sscanf(argv[1], "%d", &port_number);
    if(port_number < 0 || port_number > 65535){
        fprintf(stderr, "Port number not valid\n");
        return false;
    }

    DIR* dir = opendir(argv[2]);
    if(dir){
        closedir(dir);
        int dir_path_len = strlen(argv[2]);
        for(int i=dir_path_len-1; i>0; i--)
            if(argv[2][i] != '/'){
                argv[2][i+1] = '\0';
                return true;
            }
    }
    else if(errno == ENOENT){
        fprintf(stderr, "Directory doesn't exist\n");
        return false;
    }
    else{
        fprintf(stderr, "Failed to open directory\n");
        return false;        
    }
    return true;
}

int main(int argc, char **argv)
{
    if(!input_arguments_valid(argc, argv))
		return EXIT_FAILURE;
    int port;
	sscanf(argv[1], "%d", &port);
    char *directory = argv[2];
    
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0){
        fprintf(stderr, "Socket error\n");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
        fprintf(stderr, "Bind error\n");
        return EXIT_FAILURE;
    }

    if(listen (sock_fd, 64) < 0){
        fprintf(stderr, "Listen error\n");
        return EXIT_FAILURE;
    }

    for(;;) {
        int connected_sock_fd = accept(sock_fd, NULL, NULL);
        if(connected_sock_fd < 0){
            fprintf(stderr, "Accept error\n");
            return EXIT_FAILURE;
        }

        if(!serve_client(connected_sock_fd, CONNECTION_MAX_TIME, directory))
            return EXIT_FAILURE;

        if(close(connected_sock_fd) < 0){
            fprintf(stderr, "Close error");
            return EXIT_FAILURE;
        }
    }
}