#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;

typedef struct node
{
    int data;
    struct node* next;
}node,* node_p,** node_pp;

node_p buy_newnode(int data)
{
    node_p newnode = (node_p)malloc(sizeof(node));
    if(newnode==NULL)
    {
        perror("malloc");
        return NULL;
    }
    newnode->next=NULL;
    newnode->data=data;
    return newnode;
}
void init_list(node_pp list)
{
    *list=(node_p )malloc(sizeof(node));
    if(list==NULL)
    {
        printf("malloc");
    }
    (*list)->next=NULL;
}
void del_node(node_p node)
{
    free(node);
    node=NULL;
}
void push_head(node_p list,int data)
{
    assert(list);
    node_p newnode=buy_newnode(data);
    newnode->next=list->next;
    list->next=newnode;
}
void pop_front(node_p list,int *data)
{
    if(list->next!=NULL)
    {
        node_p del=list->next;
        *data=del->data;
        list->next=del->next;
        del_node(del);
        return ;
    }
    printf("list is empty\n");

}

void destory_list(node_p list)
{
    node_p del=NULL;
    while(list->next!=NULL)
    {
        del=list->next;
        list->next=del->next;
        del_node(del);
    }
    del_node(list);
}
void show_list(node_p list)
{
    assert(list);
    while(list->next!=NULL)
    {
        list=list->next;
        printf("%d ",list->data);
    }
    printf("\n");

}

void * producer_run(void *arg)
{
    node_p list=(node_p)arg;    
    while(1)
    {
        sleep(1);
        pthread_mutex_lock(&mylock);
        int data=rand()%1000;
        push_head(list,data);
        pthread_mutex_unlock(&mylock);
        printf("producer: data:%d\n",data);
        pthread_cond_signal(&mycond);
    }

}

void * consumer_run(void *arg)
{   
    node_p list=(node_p)arg;    
    while(1)
    {
        pthread_mutex_lock(&mylock);
        while(list->next==NULL)
      {
          pthread_cond_wait(&mycond,&mylock);
      }
        int data=0;
        pthread_mutex_unlock(&mylock);
        pop_front(list,&data);
        printf("consumer :data:%d\n",data);
    }
    
}

int main()
{
    node_p list=NULL;
    init_list(&list);
    printf("init_list cuccess\n");
    pthread_t proid;
    pthread_t conid;
    
    pthread_create(&conid,NULL,consumer_run,(void *)list);
    pthread_create(&proid,NULL,producer_run,(void *)list);
    
    pthread_join(proid,NULL);
    pthread_join(conid,NULL);

    pthread_mutex_destroy(&mylock);
    pthread_cond_destroy(&mycond);

    destory_list(list);
    return 0;
}
