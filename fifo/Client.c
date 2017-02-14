#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
int main()
{
    int fd=open("./fifo",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 1;
    }
    char buf[1024];
    while(1)
    {
        int ret=read(fd,buf,sizeof(buf)-1);
        if(ret>0)
        {
            buf[ret]='\0';
        }
        else
        {
            perror("read");
            break;
        }
        printf("%s",buf);
    }
    close(fd);
    return 0;
}
