#ifndef __HTTPD_H__
#define __HTTPD_H__

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<assert.h>

#define NORMAL 0
#define WARNING 1
#define FATAL 2

#define SIZE 4096
#define METHOD_SIZE 64
#define URL_SIZE SIZE
int startup(const char *_ip, int _port);

void print_log(char *log_massage,int level);

int  handler_sock(int sock);

#endif //!__HTTPD_H__
