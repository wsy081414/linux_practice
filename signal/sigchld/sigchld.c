#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
void sig_child(int signo)
{
    printf("捕捉到SIGCHLD\n");
    return ;
}
int main()
{
    pid_t id=fork();
    if(id==0)
    {
        printf("hehe\n");

    }
    else
    {
        struct sigaction set,oset;
        set.sa_handler=sig_child;
        sigemptyset(&set.sa_mask);
        set.sa_flags=0;
        sigaction(SIGCHLD,&set,NULL);
        waitpid(-1,NULL,0);
    }
    return 0;
}
