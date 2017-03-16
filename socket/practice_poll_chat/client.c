#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<poll.h>
#include<fcntl.h>
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage : %s [peer_ip] [peer_port]",argv[0]);
        return 1;
    }
    
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }

    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(atoi(argv[2]));
    peer.sin_addr.s_addr = inet_addr(argv[1]);

    if(connect(sock, (struct sockaddr *)&peer, sizeof(peer)) < 0)
    {
        perror("connect");
        close(sock);
        return 3;
    }

    //注册文件描述符号，以及事件
    struct pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sock;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;

    char read_buf[1024];
    int pipefd[2];

    int ret = pipe(pipefd);
    if(ret < 0)
    {
        perror("pipe");
        return 4;  
    }

    while(1)
    {
        int _r = poll(fds, 2, -1);
        if(_r < 0)
        {
            perror("poll");
            break;
        }
        if(fds[1].revents & POLLRDHUP)
        {
            printf("server close the connect\n");
            break;
        }
        else if(fds[1].revents & POLLIN)
        {
            read(fds[1].fd ,read_buf ,sizeof(read_buf)-1 );
            printf("%s\n",read_buf);
        }
        if(fds[0].revents & POLLIN)
        {
            splice(0, NULL, pipefd[1], NULL, 32768,
                  SPLICE_F_MORE | SPLICE_F_MOVE);
            splice(pipefd[0], NULL, sock, NULL, 32768, 
                  SPLICE_F_MORE | SPLICE_F_MOVE);
        }
    }





    close(sock);
    return 0;
}
