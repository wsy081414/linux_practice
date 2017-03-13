#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s [local ip] [local port]\n",argv[0]);
        return 1;
    }

    //建立客户机套接字体
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 2;
    }

    //创建接受的服务器套接字
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = ntohs(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);
    
    //进行连接操作
    if(connect(sock,(struct sockaddr *)&server,sizeof(server)))
    {
        perror("connect");
        return 3;
    }

    //客户机进行操作
    char buf[1024];
    while(1)
    {
        printf("client send: ");
        fflush(stdout);
        //客户机进行发送数据给服务器
        ssize_t _r = read(0,buf,sizeof(buf)-1);
        buf[_r - 1] = '\0';
        write(sock,buf,_r);
    }

    close(sock);
    return 0;
}
