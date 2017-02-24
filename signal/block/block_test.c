#include<stdio.h>
#include<signal.h>
void sig_run(int signo)
{
    printf("h0h\n");
}
int main()
{
    sigset_t set,oset;
    sigemptyset(&set);
    
    

     signal(SIGINT,sig_run);

    while(1);


    return 0;
}
