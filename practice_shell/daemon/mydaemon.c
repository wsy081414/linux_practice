#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("%d\n",getpid()+1);
    fflush(stdout);
    daemon(0,0);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
