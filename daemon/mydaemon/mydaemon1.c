#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
void mydaemon()
{
    umask(0);

    if(fork()>0)
    {
        exit(2);
    }
    setsid();

    chdir("/");

    close(0);
    close(1);
    close(2);

    signal(SIGCHLD,SIG_IGN);
}
int main()
{
    //mydaemon();
    while(1)
    {

    }
    return 0;
}
