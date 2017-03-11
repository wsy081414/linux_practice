#include<stdio.h>
#include<unistd.h>

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
    local.sin_port = htons(atoi(argc[2]));
    local.sin_addr.s_addr = inet_addr(argc[1]);

    if(bind(sock,(struct sockaddr *)&local,sizeof(local)) < 0)
    {
        perror("bind");
        return 3;
    }
    
    while(1)
    {
        printf("echo to server #\n");
        fflush(stdin);

        ssize_t s = sendto
    }

    struct_
    return 0;
}
