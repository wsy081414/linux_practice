#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>

//关于锁的初始化
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int count=0;

void * pthread_run(void *arg)
{
    int val=0;
    int i=0;
    while(i<5000)
    {
        //在临界区加上互斥锁，这样就可解决线程访问冲突的问题了
        pthread_mutex_lock(&mutex);
        i++;
        val=count;
        printf("pthread: %lu,count:%d\n",pthread_self(),count);
        count =val+1;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1,NULL,&pthread_run,NULL);
    pthread_create(&tid2,NULL,&pthread_run,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    printf("couint :%d\n",count);
    return 0;
}
