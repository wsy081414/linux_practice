/*************************************************************************
	> File Name: producer_consumer.c
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Tue 21 Feb 2017 06:04:34 PM PST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define Blank 64
#define Data 0

//环型队列生消模型
int bank[Blank];
sem_t pro,cons;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
void* producer_run(void *arg)
{
    int i=0;

    while(1)
    {
        sem_wait(&pro);
 
//        pthread_mutex_lock(&mutex);
        int prodata=rand()%1000;
        i%=Blank;
        bank[i]=prodata;
        printf("producer make done!!,data:%d\n",prodata);
        i++;
//        pthread_mutex_unlock(&mutex);
        sem_post(&cons);
        sleep(1);
    }
}
void* consumer_run(void *arg)
{
    int c=0;
    while(1)
    {
        sem_wait(&cons);
//        pthread_mutex_lock(&mutex1);
        c%=Blank;
        int consudata=bank[c];
        printf("consumer make done,data:%d\n",consudata);
        c++;
//        pthread_mutex_unlock(&mutex1);
        sem_post(&pro);
        sleep(1);
    }
}
int main()
{

    sem_init(&pro,0,Blank);
    sem_init(&cons,0,Data);

    pthread_t producer,consumer;
    pthread_t producer1,consumer1;

    pthread_create(&producer,NULL,producer_run,NULL);
    pthread_create(&consumer,NULL,consumer_run,NULL);
    pthread_create(&producer1,NULL,producer_run,NULL);
    pthread_create(&consumer1,NULL,consumer_run,NULL);


    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);

    sem_destroy(&pro);
    sem_destroy(&cons);

    return 0;
}
