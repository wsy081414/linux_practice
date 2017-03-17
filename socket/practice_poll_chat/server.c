#define _GNU_SOURCE 1
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<poll.h>

#define LIMIT_FD 65535
#define LIMIT_USER 5
#define BUF_SIZE 1024
//客户数据：包含客户的socket地址，待写到客户端的数据的位置、从客户端读入数据。

struct client_data
{
    struct sockaddr_in address;
    char* write_buf;    //写入客户端段的数据的位置
    char buf[BUF_SIZE];    //客户端读入的数据
};

int StartUp(int port,char *ip_addr)
{
    assert(ip_addr);
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(2);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip_addr);

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
//设置文件描述符为非阻塞状态
int setnoblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return old_option;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s [local_ip] [local_port]\n",argv[0]);
        return 1;
    }

    //建立监听socket 
    int listen_sock = StartUp(atoi(argv[2]),argv[1]);

    //创建users数组，分配client数据对象的文件描述符。利用它来进行索引用户数据以及发数据
    struct client_data* users = (struct client_data *)malloc(sizeof(struct client_data)*LIMIT_FD);
    //client_data users[LIMIT_FD];

    //虽然有足够多的client_data,但是依然要限制用户数量，事件最大
    struct pollfd fds[LIMIT_USER+1];

    int user_count = 0;
    int i = 0;

    for(i = 1; i <= LIMIT_USER; ++i)
    {
        fds[i].fd = -1;
        fds[i].events = 0;
    }

    fds[0].fd = listen_sock;//设置监听端口
    fds[0].events = POLLIN|POLLERR;//监听端口设置可读和错误事件
    fds[0].revents = 0;


    while(1)
    {
        //永远等待，当准备好再去提交给应用程序。
        int ret = poll(fds, user_count+1, -1);

        if(ret < 0)
        {
            printf("poll faile\n");
            break;
        }

        for(i = 0; i < user_count+1; ++i)
        {
            //此时为监听套接字，有新连接来，监听套接字接受到可读事件
            if((fds[i].fd == listen_sock) && (fds[i].revents & POLLIN))
            {
                struct sockaddr_in peer;
                socklen_t peer_len = sizeof(peer);

                int sock = accept(listen_sock,\
                                  (struct sockaddr *)&peer,&peer_len);
                if(sock < 0)
                {
                    perror("accept");
                    continue;
                }

                printf("new user :ip:%s,port:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));

                // 如果请求太多，则关闭请求连接。
                if(user_count >= LIMIT_USER)
                {
                    const char *msg = "Too many users!!!\n";
                    printf("%s",msg);
                    write(sock, msg, sizeof(msg) );
                    close(sock);
                    continue;
                }
                //相对于新连接，同时去修改fds，和users数组对应连接的文件描述符sock的客户数据。
                user_count++;
                users[sock].address = peer;

                //设置非阻塞
                setnoblocking(sock);
                fds[user_count].fd = sock;
                fds[user_count].events = POLLIN | POLLERR | POLLRDHUP;
                fds[user_count].revents = 0;
                printf("come a new user, now have %d users\n",user_count);
            }
            //对于出现错误信息
            else if(fds[i].revents & POLLERR)
            {
                printf("get an error from %d\n",fds[i].fd);
                //...

                continue;
            }
            //如果客户端关闭连接。此时检测到客户端断开的请求，所以这个时候触发这个事件
            else if(fds[i].revents & POLLRDHUP)
            {
                //服务器也许要关闭连接，并且把user_count减1
                //这里的减相当于去移动了文件描述符，把最大的放到了需要减的那个了。
                //
                users[fds[i].fd] = users[fds[user_count].fd];
                close(fds[i].fd);
                fds[i] = fds[user_count];
                i--;
                user_count--;
                printf("a client left\n");
            }
//连接套接字可读
            else if(fds[i].revents & POLLIN)
            {
                int sock = fds[i].fd;
                memset(users[sock].buf, 0,sizeof(users[sock].buf));
                ret = read(sock, users[sock].buf, sizeof(users[sock].buf) - 1);

                printf("client :%s\n",users[sock].buf);
                if(ret > 0)
                {
                    //收到客户数据，此时通知其他的socket接受数据
                    users[sock].buf[ret] = 0;
                    int j = 0;
                    for(j = 1; j <= user_count; ++j)
                    {
                        if(fds[j].fd == sock)
                        {
                            continue;
                        }
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;

                        users[fds[j].fd].write_buf = users[sock].buf;
                    }
                }
                else if(ret < 0)
                {
                    //读取错误，关闭连接
                    if(errno != EAGAIN)
                    {
                        perror("read");
                        close(sock);
                        users[fds[i].fd] = users[fds[user_count].fd];
                        fds[i] = fds[user_count];
                        i--;
                        user_count--;
                    }
                }
            }
            else if(fds[i].revents & POLLOUT)
            {
                //连接套接字可写
                int sock =fds[i].fd;
                //判断是否可写
                if(! users[sock].write_buf)
                {
                    continue;
                }
                ret = write(sock,users[sock].write_buf,\
                            BUF_SIZE-1);
                users[sock].write_buf = NULL;
                //写完以后重新注册fds[i]的可读事件
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
            }
            }


    close(listen_sock);
    return 0;
}
