#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
int main()
{
    umask(0);
    if(mkfifo("./fifo",S_IFIFO|0666)==-1)
    {
        perror("fifo create");
        return 1;
    }
    int fd=open("./fifo",O_WRONLY);
    if(fd<0)
    {
        perror("open");
    }
    char buf[1024];
    while(1)
    {
        int _s=read(0,buf,1023);
        if(_s>0)
        {
            buf[_s]='\0';
        }
        else{
            perror("read");
        }
        int ret=write(fd,buf,strlen(buf));
        if(ret<0)
        {
            perror("write");
            break;
        }
    }
    close(fd);
    return 0;
}
