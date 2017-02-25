#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_alarm(int signo)
{

}
void mysleep(int seconds)
{
    struct sigaction set,oset;
    set.sa_handler=sig_alarm;
    sigemptyset(&set.sa_mask);
    set.sa_flags=0;
    sigaction(SIGALRM,&set,&oset);
    //这里我们首先阻塞SIGALRM
    alarm(seconds);
    
    //解除阻塞SIGALRM信号
    pause();
    unsigned int unslept=alarm(0);
    sigaction(SIGALRM,&oset,NULL);
}
int main()
{
    while(1)
    {
        mysleep(2);
        printf("2 seconds success\n");
    }
    return 0;
}
