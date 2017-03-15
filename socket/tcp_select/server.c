/*************************************************************************
> File Name: server.c
> Author:yuzhe 
> Mail:953659912@qq.com 
> Created Time: Tue 14 Mar 2017 05:43:30 AM PDT
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//设定一个select数组
#define __SIZE__ 64
int gfds[__SIZE__];

int startup(int port,char *ip)
{
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

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage : %s [local_ip] [local_port]\n",argv[0]);
        return 5;
    }
    //创建监听套接字
    int listen_sock = startup(atoi(argv[2]), argv[1]);

    int i=0;

    //让记录套接字的数组初始化为-1.
    for(;i < __SIZE__;i++)
    {
        gfds[i] = -1;
    }

    while(1)
    {
        //监听套接字插入gfds
        gfds[0] = listen_sock;
        
        //定义max最终在nfds使用
        int max_fd = -1;
        
        //创建文件描述符集
        fd_set rfds;
        
        //对文件描述符集进行初始化
        FD_ZERO(&rfds);
        
        //将监听套接字设置在文件描述符集合当中
        FD_SET(listen_sock,&rfds);

        //进行查找最大的max_fd, 为了后续操作nfds
        int k = 0;
        for(;k < __SIZE__;k++)
        {
            if(gfds[k] != -1)
            {
                if(k > max_fd)
                {
                    max_fd = k;
                }
            }
        }
        printf("max_fd : %d\n",max_fd);
        
        //设置timeout值
        struct timeval timeout={5,0};

        //进行select I/O多路复用
        switch(select(max_fd+1,&rfds,NULL,NULL,&timeout))
        {
            case -1:
            {
                perror("select");
                break;
            }
            break;
            case 0:
            {
                printf("time out\n");
                continue;
            }
            break;
            default:
            {
                int j = 0;
                for(;j < __SIZE__;j++)
                {
                    if(gfds[j] == -1)
                    {
                        continue;
                    }
                    else if(FD_ISSET(gfds[j],&rfds) && gfds[j] == listen_sock)
                    {
                        struct sockaddr_in peer;
                        socklen_t len = sizeof(peer);
                        int sock =accept(listen_sock,\
                                         (struct sockaddr *)&peer,&len);
                        printf("client :ip:%s,port:%d\n",\
                               inet_ntoa(peer.sin_addr),\
                               ntohs(peer.sin_port));
                        if(sock < 0)
                        {
                            perror("accept");
                            continue;
                        }
                        else
                        {
                            int m = 0;
                            for(;m < __SIZE__;m++)
                            {
                                if(gfds[m] == -1)
                                {
                                    gfds[m] = sock;
                                    FD_SET(gfds[m],&rfds);
                                    break;
                                }
                            }
                            if(k == __SIZE__)
                            {
                                printf("too many client\n");
                            }
                        }
                    }
                    else if(FD_ISSET(gfds[j],&rfds))
                    {
                        char buf[1024];
                        ssize_t _r = read(gfds[j],buf,sizeof(buf-1));
                        if(_r > 0)
                        {
                            buf[_r] = 0;
                            printf("client echo # %s\n",buf);
                        }
                        else if(_r == 0)
                        {
                            printf("client is closed\n");
                            close(gfds[i]);
                            gfds[j] = -1;
                            continue;
                        }
                        else
                        {
                            perror("read");
                            return 5;
                        }
                    }
}
break;
            }
            break;
        }
        }
        close(listen_sock);
        return 0;
}

