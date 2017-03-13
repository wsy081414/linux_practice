#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<assert.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
int startup(int port,char *ip)
{
    assert(ip);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }
 
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);

    if(bind(sock,(struct sockaddr *)&local,sizeof(local)) < 0)
    {
        perror("bind");
        exit(3);
    }

    if(listen(sock,5) < 0)
    {
        perror("listen");
        exit(4);
    }
    return sock;
}

void *thread_run(void *arg)
{
    int sock = *((int *)arg);
    
    while(1)
    {
        char buf[1024];

        ssize_t s = read(sock,buf,sizeof(buf)-1);
        if(s > 0)
        {
            buf[s] = 0;
            printf("client echo # %s\n",buf);
        }
        else
        {
            printf("client quit\n");
            break;
        }
    }
    close(sock);
    return 0;
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s [ip address] [port]\n",argv[0]);
        return 1;
    }
    int listen_sock = startup(atoi(argv[2]),argv[1]);

    while(1)
    {
        struct sockaddr_in peer;
        socklen_t socklen = sizeof(peer);
        int sock = accept(listen_sock,(struct sockaddr *)&peer,&socklen);

        pthread_t tid;
        printf("peer ip: %s,port: %d\n",\
               inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
        pthread_create(&tid,NULL,thread_run,&sock);
        
        //线程分离.
        pthread_detach(tid);
    }

    close(listen_sock);
    return 0;
}
