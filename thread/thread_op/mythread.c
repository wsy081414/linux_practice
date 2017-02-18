#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
void *thread_run(void *arg)
{
    pthread_t mainid = *(pthread_t*)arg;
    int count =5;
    while(count--)
    {
        sleep(1);
        printf("new thread: pid:%d,ppid:%d,tid:%lu\n",getpid(),getppid(),pthread_self());
    }  
    
    printf("new overi\n");
    pthread_cancel(mainid);
    //return (void *)77;
    //pthread_exit((void*)77);
}
int main()
{
    pthread_t tid;
    pthread_t mainid = pthread_self();
    int ret = pthread_create(&tid,NULL,&thread_run,(void*)&mainid);
    if(ret < 0)
    {
        printf("pthread_create failed");
        return -1;
    }
   /*while(1)
    {
        //main thread
        sleep(1);
        printf("main thread: pid:%d,ppid:%d,tid:%lu\n",getpid(),getppid(),pthread_self());

    }*/

    printf("main thread: pid:%d,ppid:%d,tid:%lu\n",getpid(),getppid(),pthread_self());
    int errorcode=0;
    sleep(3);
    pthread_join(tid,(void **)&errorcode); 
    printf("errorcode:%d\n",errorcode);
    printf("main overi\n");
    return 0;
}
