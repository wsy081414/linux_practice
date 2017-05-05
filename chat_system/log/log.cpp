/*************************************************************************
	> File Name: log.cpp
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sat 22 Apr 2017 10:04:34 PM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

void print_log(string msg,int level)
{
    #define __debug__
    #ifdef __debug__
    char *log_file_path = "log/filelog"
    int fd = open(log_file_path,O_WRONLY|O_APPEND|O_CREAT,0644);
    string tmp = msg;
    tmp+=log_level[level];
    write(fd ,tmp.c_str(), tmp.size());
    close(fd);
    #endif
    
}
