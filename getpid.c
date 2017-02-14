/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Fri 06 Jan 2017 11:56:51 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main()
{
    while(1)
    {
        printf("hello world %d,%d\n",getpid(),getppid());
        sleep(1);

    }


}
