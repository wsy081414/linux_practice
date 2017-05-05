/*************************************************************************
	> File Name: dataPool.cpp
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sun 23 Apr 2017 01:57:20 AM PDT
 ************************************************************************/

#include "dataPool.h"
using namespace std;

dataPool::dataPool(const int &capacity)
    :_size(0)
    ,_capacity(capacity)
    ,_pool(capacity)
{
    producter_count = 0;
    consumer_count = 0;
    sem_init(&blank, 0 ,0);
    sem_init(&data, 0 ,0);

}
dataPool::~dataPool();
{
    _size = 0;
    _capacity = 0;
    sem_destroy(&blank);
    sem_destroy(&data);
}
void dataPool::getData(string &outstring)
{
    
    sem_wait(data);
    outstring = _pool[consumer_count++];
    size--;
    consumer_count %= _capacity;
    sem_post(blank);
}
void dataPool::putData(string &instring)
{
    sem_wait(blank);
    _pool[producter_count++] = instring;
    size++;
    producter_count %= _capacity;

    sem_post(data);
}
