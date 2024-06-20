#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>
#include "get_request.h"
#include <dirent.h>
#include <errno.h>

#define BUFFER_SIZE 10000000 // 10 MB
u_int8_t http_response[BUFFER_SIZE+1];

long get_file_size(char *path){
    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        fprintf(stderr, "Failed to open file %s\n", path);
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    long res = ftell(fp);
    fclose(fp);
    return res;
}

bool file_to_buffer(char *buffer, char *file_path, int buffer_offset, int file_size){
    FILE *fp = fopen(file_path, "r");
    if(fp != NULL){
        int readBytes = fread(buffer, sizeof(char), BUFFER_SIZE-buffer_offset, fp);
        if(readBytes < file_size){
            fprintf(stderr, "Reading file error\n");
            return false;
        }
        fclose(fp);
        return true;
    }
    else{
        fprintf(stderr, "Failed to open file\n");
        return false;
    }
}

char *dest_directory(char *host){
    char *colon = strchr(host, ':');
    if(colon == NULL)
        return NULL;
    *colon = '\0';
    return host;
}

void add_to_path(char *path, char *file){
    int path_len = strlen(path);
    if(path[path_len-1] != '/')
        strcat(path, "/");
    strcat(path, file);
}

void dest_file_path(char *dir, char *filePath, char *buffer){
    strcpy(buffer, dir);
    if(filePath[0] != '\0')
        add_to_path(buffer, filePath);
}

int fill_header(char *response_code, char *content_type, int content_length, char *location){
    char first_line[200];
    strcpy(first_line, "HTTP/1.1 ");
    strcat(first_line, response_code);
    strcat(first_line, "\r\n");
    int first_line_len = strlen(first_line);
    memcpy(http_response, first_line, first_line_len);

    if(location != NULL){
        char location_line[200];
        strcpy(location_line, "Location: ");    
        strcat(location_line, location);
        strcat(location_line, "\r\n");
        int location_line_len = strlen(location_line);
        memcpy(http_response+first_line_len, location_line, location_line_len);
        first_line_len += location_line_len;
    }

    char second_line[200];
    strcpy(second_line, "Content-Length: ");
    char content_len_str[20];  
    sprintf(content_len_str, "%d", content_length); 
    strcat(second_line, content_len_str);
    strcat(second_line, "\r\n");
    int second_line_len = strlen(second_line);
    memcpy(http_response+first_line_len, second_line, second_line_len);

    char third_line[200];
    strcpy(third_line, "Content-Type: ");
    strcat(third_line, content_type);
    strcat(third_line, "\r\n\r\n");
    int third_line_len = strlen(third_line);
    memcpy(http_response+first_line_len+second_line_len, third_line, third_line_len);

    return first_line_len + second_line_len + third_line_len;
}

char *get_file_extension(const char *filename){
    char *dot = strrchr(filename, '.');
    if(dot == NULL) 
        return NULL;
    return dot + 1;
}

void fill_content_type(char *content_type, char* filePath){
    char *file_extension = get_file_extension(filePath);
    if(file_extension == NULL){
        strcpy(content_type, "application/octet-stream");
        return;
    }
    
    if(strcmp(file_extension, "txt") == 0)
        strcpy(content_type, "text/plain;charset=utf-8");
    else if(strcmp(file_extension, "html") == 0)
        strcpy(content_type, "text/html;charset=utf-8");
    else if(strcmp(file_extension, "css") == 0)
        strcpy(content_type, "text/css;charset=utf-8");
    else if(strcmp(file_extension, "jpg") == 0 || strcmp(file_extension, "jpeg") == 0)
        strcpy(content_type, "image/jpeg");
    else if(strcmp(file_extension, "png") == 0)
        strcpy(content_type, "image/png");
    else if(strcmp(file_extension, "pdf") == 0)
        strcpy(content_type, "application/pdf");
    else
        strcpy(content_type, "application/octet-stream");
}

int prepare_200_response(char *filePath){
    char response_code[] = "200 OK";
    
    char content_type[100];
    fill_content_type(content_type, filePath);

    int file_size = get_file_size(filePath);
    if(file_size < 0)
        return -1;

    int offset = fill_header(response_code, content_type, file_size, NULL);
    if(!file_to_buffer((char*)(http_response+offset), filePath, offset, file_size))
        return -1;
    return offset + file_size;
}

int prepare_301_response(char *filePath){
    char response_code[] = "301 Moved Permanently";
    char content_type[] = "text/html;charset=utf-8";

    char dest_file_path[200];
    strcpy(dest_file_path, filePath);
    add_to_path(dest_file_path, "index.html");

    char message[1000];
    strcpy(message, "<!DOCTYPE html>\n<html>\n<title>301 Moved Permanently</title>\n");
    strcat(message, "<body>\n\n<h1>Moved Permanently</h1>\n\n<p>Can't access directory - redirection to index.html");
    strcat(message, "</p>\n\n</body>\n</html>");
    int message_len = strlen(message);

    int offset = fill_header(response_code, content_type, message_len, dest_file_path);
    memcpy((http_response+offset), message, message_len);
    return offset + message_len; 
}

int prepare_403_response(){
    char response_code[] = "403 Forbidden";
    char content_type[] = "text/html;charset=utf-8";
    char message[1000];
    strcpy(message, "<!DOCTYPE html>\n<html>\n<title>403 Forbidden</title>\n");
    strcat(message, "<body>\n\n<h1>Forbidden</h1>\n\n<p>Can't access files outside the domain's directory.");
    strcat(message, "</p>\n\n</body>\n</html>");
    int message_len = strlen(message);
    int offset = fill_header(response_code, content_type, message_len, NULL);
    memcpy((http_response+offset), message, message_len);
    return offset + message_len; 
}

int prepare_501_response(){
    char response_code[] = "501 Not Implemented";
    char content_type[] = "text/html;charset=utf-8";
    char message[1000];
    strcpy(message, "<!DOCTYPE html>\n<html>\n<title>501 Not Implemented</title>\n");
    strcat(message, "<body>\n\n<h1>Not Implemented</h1>\n\n<p>Server failed to interpret HTTP request.");
    strcat(message, "</p>\n\n</body>\n</html>");
    int message_len = strlen(message);
    int offset = fill_header(response_code, content_type, message_len, NULL);
    memcpy((http_response+offset), message, message_len);
    return offset + message_len;    
}

int prepare_404_response(char *filePath){
    char response_code[] = "404 Not Found";
    char content_type[] = "text/html;charset=utf-8";
    char message[1000];
    strcpy(message, "<!DOCTYPE html>\n<html>\n<title>404 Not Found</title>\n");
    strcat(message, "<body>\n\n<h1>Not Found</h1>\n\n<p>The requested file ");
    strcat(message, filePath);
    strcat(message, " was not found on this server.</p>\n\n</body>\n</html>");
    int message_len = strlen(message);
    int offset = fill_header(response_code, content_type, message_len, NULL);
    memcpy((http_response+offset), message, message_len);
    return offset + message_len;
}

bool is_directory(char *filePath){
    if(filePath[0] == '\0')
        return true;
    DIR* dir = opendir(filePath);
    if(dir == NULL)
        return false;
    closedir(dir);
    return true;
}

bool is_file(char *filePath){
    FILE *fp = fopen(filePath, "r");
    if (fp == NULL)
        return false;
    fclose(fp);
    return true;
}

bool resource_forbidden(char *filePath){
    int cur_level = 0;
    char *cur_path_pos = filePath;
    while(true){
        char *slash = strchr(cur_path_pos, '/');
        if(slash == NULL)
            return false;
        *slash = '\0';
        if(strcmp(cur_path_pos, "..") == 0){
            cur_level--;
            if(cur_level < 0){
                *slash = '/';
                return true;
            }
        }
        else if(cur_path_pos[0] != '\0')
            cur_level++;
        cur_path_pos = slash+1;
        *slash = '/';
    }
    return false;
}

bool resource_exists(char *filePath){
    return is_directory(filePath) || is_file(filePath);
}

bool send_all(int sockfd, int n){
    size_t n_left = n;
    int offset = 0;
    while (n_left > 0){
        ssize_t bytes_sent = send(sockfd, http_response+offset, n_left, 0);
        if (bytes_sent < 0){
            fprintf(stderr, "Send error\n");
            return false;
        }
        n_left -= bytes_sent;
        offset += bytes_sent;
    }
    return true;
}

bool send_response(int client_fd,  RequestParameters_t *requestParameters, char *directory){
    char *dest_dir_name = dest_directory(requestParameters->host);
    if(requestParameters->bad_request || dest_dir_name == NULL){
        int response_len = prepare_501_response();
        if(!send_all(client_fd, response_len))
            return false;
        return true;
    }

    char dest_dir_path[200];
    dest_file_path(directory, dest_dir_name, dest_dir_path);
    DIR* dir = opendir(dest_dir_path);
    if(dir == NULL){
        fprintf(stderr, "No such directory found\n");
        return false;
    }

    char requested_file_path[200];
    dest_file_path(dest_dir_path, requestParameters->requested_path, requested_file_path);

    int total_response_len = 0;
    if(resource_forbidden(requestParameters->requested_path))
        total_response_len = prepare_403_response();
    else if(!resource_exists(requested_file_path))
        total_response_len = prepare_404_response(requestParameters->requested_path);
    else if(is_directory(requested_file_path))
        total_response_len = prepare_301_response(requestParameters->requested_path);
    else{
        total_response_len = prepare_200_response(requested_file_path);
        if(total_response_len < 0)
            return false;
    }
            
    if(!send_all(client_fd, total_response_len))
        return false;
    return true;
}