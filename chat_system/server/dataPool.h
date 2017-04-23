/*************************************************************************
	> File Name: dataPool.h
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sun 23 Apr 2017 01:57:27 AM PDT
 ************************************************************************/

#ifndef _DATAPOOL_H
#define _DATAPOOL_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class dataPool{
public:
    dataPool();
    ~dataPool();
    void getData(string& outstring);
    void putData(const string &instring);
private:
    int _size;
    int _capacity;
    sem_t blank;
    sem_t data;
    std::vector<string > _pool;
};
#endif
