/*************************************************************************
	> File Name: test.c
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sun 12 Feb 2017 11:10:04 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    while(1)
    {
    printf("[yuzhe@localhost /]￥");
    fflush(stdout);
    char line[1024];
    int s=read(0,line,1024);
    if(s>0)
    {
        line[s]=0;
    }else{
    continue;}
    char *start=line;
    int i=1;
    char * myargv[10];
    myargv[0]=start;
    
    while(*start)
    {
        if(isspace(*start))
        {
            *start='\0';
            start++;
            myargv[i++]=start;
        }
        else{
            start++;
        }
    }
    myargv[i-1]=NULL;
    pid_t pid=fork();
    if(pid==0)
    {
        execvp(myargv[0],myargv);
        perror("error\n");
        exit(1);
    }
    else{
        printf("father\n");
        wait(NULL);
    }
    }
    return 0;
}
