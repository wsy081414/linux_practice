/*************************************************************************
	> File Name: procBar.c
	> Author: 
	> Mail: 
    > Create:d Time: Fri 30 Dec 2016 11:56:16 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
void procbar()
{
    char arr[102];

    int rate=0;
    char tmp[]="-\\|/";
    memset(arr,0,sizeof(arr));
    while(rate<=100)
    {
        printf("[%-100s][%d%%][%c]\r",arr,rate,tmp[rate%4]);

        arr[rate]='=';
        rate++;
        fflush(stdout);
        usleep(50000);
    }
    printf("\n");
}
int main()
{
    procbar();
    return 0;
}
