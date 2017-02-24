#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_run(int signo)
{
    int count =0;
    while(count++)
    {
    }
    printf("%d\n",count);
}
int main()
{
    int count=0;
    signal(SIGALRM,sig_run);
    alarm(1);

    return 0;
}
