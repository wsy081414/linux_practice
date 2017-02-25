#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
void sig_child(int signo)
{
    printf("hehe\n");
}
int main()
{
    pid_t id=fork();
    if(id==0)
    {
        exit(2);
    }
    else
    {
        struct sigaction set;
        set.sa_handler=sig_child;
        sigemptyset(&set.sa_mask);
        set.sa_flags=0;
        sigaction(SIGCHLD,&set,NULL);
        wait(NULL);
    }

    return 0;
}
