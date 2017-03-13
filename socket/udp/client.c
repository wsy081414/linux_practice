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
    

    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(atoi(argv[2]));
    peer.sin_addr.s_addr = inet_addr(argv[1]);
    socklen_t socklen = sizeof(struct sockaddr_in); 
    

    while(1)
    {
        char buf[1024];
        memset(buf,0,sizeof(buf));
        printf("echo to server #:");
        fflush(stdin);
        ssize_t s = read(0,buf,sizeof(buf)-1);
        if(s > 0)
        {
            buf[s-1] = '\0';
            ssize_t _s = sendto(sock,buf,s,0,(struct sockaddr *)&peer,socklen);
            printf("%s \n",buf);
        }
        else
        {
            perror("read");   
            continue;
        }

    }

    return 0;
}
