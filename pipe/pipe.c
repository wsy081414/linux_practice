#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
int main()
{
    int pipfd[2]={0};
    int s=pipe(pipfd);
    if(s<0)
    {
        perror("pipe");
        return 1;
    }

    pid_t id=fork();
    if(id==0)
    {
        //child---write 
        close(pipfd[0]);
        char *msg="yes";
        int count=20;
        while(1)
        {
            write(pipfd[1],msg,strlen(msg));
            sleep(1);
        }
        close(pipfd[1]);
    }  
    else 
    {
        close(pipfd[1]);
        char buf[1024];
        int count=10;
        while(count)
        {
            int _s=read(pipfd[0],buf,sizeof(buf)-1);
            if(_s>0)
            {
                buf[_s]='\0';
            }
            else
            {
                perror("read");
                return 2;
            }
            printf("father proc:%s\n",buf);
        }
        close(pipfd[0]);
        waitpid(id,NULL,0);
    }
    return 0;
}
