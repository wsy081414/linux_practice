#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
int create_listen_sock(int port,char* address)
{
    //创建套接字
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(address);
    local.sin_port = htons(port);

    if(bind(sock,(struct sockaddr *)&local,sizeof(local)) < 0)
    {
        perror("bind");
        exit(2);
    }

    if(listen(sock,5) < 0)
    {
        perror("listen");
        exit(3);
    }
    return sock;
}

int main(int argc, char *argv[])
{
    //进行判断传入参数是否合法
    if(argc != 3)
    {
        printf("Usage: %s [local ip] [local port]\n",argv[0]);
        return 1;
    }
    //创建监听套接字
    int listen_sock = create_listen_sock(atoi(argv[2]),argv[1]);

    struct sockaddr_in remote;
    socklen_t len=sizeof(remote);
    while(1)
    {
        //服务器接受客户机的连接请求
        int sock = accept(listen_sock, \
                          (struct sockaddr *)&remote,&len);
        if(sock < 0)
        {
            sleep(1);
            perror("accept");
            continue;
        }
        pid_t id;
        id = fork();
        if(id == 0)
        {
            //子进程关闭监听套接字
			close(listen_sock);
            if(fork() == 0)
            {
                printf("remote ip : %s,remote port : %d\n",\
                       inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
                //接受客户机传入的数据
                char *buf[1024];
                while(1)
                {
                    ssize_t _r = read(sock,buf,sizeof(buf)-1);
                    //这里的套接字当中考虑有数据传输和没有数据传输
                    if(_r > 0)
                    {
                        buf[_r]='\0';
                        printf("client send : %s\n",buf);
                    }
                    else
                    {
                        printf("client quit,\n");
                        break;
                    }
                }
                //孙子进程执行完以后就去退出
                close(sock);
                exit(7);
            }
			else
			{
                //儿子进程关闭，然后退出
                close(sock);
				exit(6);
			}
        }
        else
        {
            //父进程关闭套接字，回收子进程。
            close(sock);
            wait(NULL);
            continue;
        }
    }


    return 0;
}




