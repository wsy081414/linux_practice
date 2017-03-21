#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<sys/epoll.h>
#include<string.h>
#define __SIZE__ 1024
typedef struct epbuf
{
    int fd;
    char buf[1024];
}epbuf,* epbuf_p;

int startup(int port,char *ip)
{
    assert(ip);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);

    if(bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
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

epbuf_p alloc_epbuf(int sfd)
{
    epbuf_p buf = malloc(sizeof(struct epbuf));
    if(buf == NULL)
    {
        perror("malloc");
        exit(5);
    }
    buf->fd = sfd;
    return buf;
}
void del_epbuf(epbuf_p ptr)
{
    if(ptr != NULL)
    free(ptr);
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage : %s [local_ip] [local_port]\n",argv[0]);
        return 1;
    }
    int listen_sock = startup(atoi(argv[2]),argv[1]);

    int epfd = epoll_create(5);

    if(epfd < 0)
    {
        perror("epoll_create");
        return 6;
    }

    struct epoll_event listen_event;
    listen_event.data.ptr = alloc_epbuf(listen_sock);
    listen_event.events = EPOLLIN | EPOLLERR;
    if(epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&listen_event) < 0)
    {
        perror("epoll_ctl");
        return 7;
    }

    int timeout = 2000;

    struct epoll_event epfds[__SIZE__];
    while(1)
    {
        int retfd;
        switch((retfd = epoll_wait(epfd, epfds, __SIZE__, timeout)))
        {
            case -1:
            perror("epoll_wait");
            return 8;
            break;
            case 0:
            printf("timeout\n");
            break;
            default:
            {
                int i = 0;
                for(;i < retfd;i++)
                {
                    int fd = ((epbuf_p)(epfds[i].data.ptr))->fd;
                    if((fd == listen_sock) && (epfds[i].events & EPOLLIN))
                    {
                        struct sockaddr_in peer;
                        socklen_t len = sizeof(peer);
                        int ret = accept(fd, (struct sockaddr *)&peer, &len);

                        printf("IP : %s,port : %d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
                        if(ret < 0)
                        {
                            perror("accept");
                            continue;
                        }

                        epfds[i].data.ptr = alloc_epbuf(fd);
                    }//listen_sock
                    else if((fd != listen_sock) && (epfds[i].events & EPOLLIN))
                            {
                                int _r = read(fd,((epbuf_p)(epfds[i].data.ptr))->buf,__SIZE__-1);
                                if(_r < 0)
                                {
                                    perror("read");
                                    return 8;
                                }
                                else if(_r == 0)
                                {
                                    close(fd);
                                    continue;
                                }
                                else
                                {
                                    char *tmp = ((epbuf_p)(epfds[i].data.ptr))->buf;
                                    tmp[_r] = 0;
                                    printf("%s\n",tmp);
                                    epfds[i].events = EPOLLOUT;
                                    epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &epfds[i]);
                                }
                            }//sock
                            else if ((fd != listen_sock) && (epfds[i].events & EPOLLOUT))
                    {
                                char *msg="http/1.0 2000ok\r\n\r\n<html><h1>hello world</h1></html>";
                                write(fd, msg, strlen(msg));
                    }
                }
            }//default
        }//switch
    }

    return 0;
}
