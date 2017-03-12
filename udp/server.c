#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage %s [ip] [port] \n",argv[0]);
        return 1;
    }

    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t socklen = sizeof(local);

    if(bind(sock,(struct sockaddr *)&local,sizeof(local)) < 0)
    {
        perror("bind");
        return 3;
    }
    
    
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(atoi(argv[2]));
    peer.sin_addr.s_addr = inet_addr(argv[1]);
    //socklen_t socklen = sizeof(local);
    
    while(1)
    {  
        char buf[1024];
        memset(buf,0,sizeof(buf));
        ssize_t s = recvfrom(sock,buf,sizeof(buf),0, (struct sockaddr *)&peer,&socklen);
        buf[s-1]='\0';
        if(s == 0)
        {
            continue;
        }
        else if(s < 0)
        {
            perror("resvfrom");
            close(sock);
            return 4;
        }
        else
        {
            printf("recvfrom :%s\n",buf);
        }
    }

    
    return 0;
}
