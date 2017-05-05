/*************************************************************************
	> File Name: log.h
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sat 22 Apr 2017 10:04:41 PM PDT
 ************************************************************************/

#ifndef _LOG_H
#define _LOG_H
#include<iostream>
#include<string>

string log_level[]=
{
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
}

void print_log(string msg,int level);

#endif
