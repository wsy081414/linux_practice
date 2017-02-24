#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void printfspending(sigset_t *set)
{
    int i=0;
    for(i=0;i<32;i++)
    {
        if(sigismember(set,i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}
int main()
{
    sigset_t set,oset;
    sigemptyset(&set);
    printfspending(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_BLOCK,&set,NULL);
    while(1)
    {
        sigpending(&oset);
        printfspending(&oset);
        sleep(1);
    }

    return 0;
}
