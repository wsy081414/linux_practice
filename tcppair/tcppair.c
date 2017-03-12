#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
int main()
{

    int sv[2];
    int sock = socketpair(AF_LOCAL,SOCK_STREAM,0,sv);
    if(socketpair < 0)
    {
        perror("socketpair");
        return 1;
    }

    pid_t id;
    id = fork();
    if(id == 0)
    {
        close(sv[0]);
        char buf[1024];
        while(1)
        {

            //child
            char *msg="hello world";
            strcpy(buf,msg);
            write(sv[1],buf,sizeof(buf)-1);
            sleep(1);
            ssize_t r = read(sv[1],buf,sizeof(buf)-1);
            if(read > 0)
            {
                buf[r]=0;
                printf("father echo: %s\n",buf);
            }
        }

    }
    else if(id > 0) 
    {
     
        close(sv[1]);
        char buf[1024];
        while(1)
        {
            ssize_t r = read(sv[0],buf,sizeof(buf)-1);
            if(r > 0)
            {
                buf[r] = 0;
                printf("client echo # %s\n",buf);
                write(sv[0],buf,sizeof(buf)-1);
            }    
            sleep(1);
        }
    }
    else
    {
        perror("fork");
        return 2;
    }



    return 0;
}

