/*************************************************************************
	> File Name: sql_api.h
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Thu 13 Apr 2017 05:33:54 AM PDT
 ************************************************************************/

#ifndef _SQL_API_H
#define _SQL_API_H
#include<iostream>
#include<mysql.h>
#include<string>

using namespace std;
class sqlopt
{
public:
    sqlopt();
    ~sqlopt();
    int sql_connect();
    int sql_insert(const string& data);
    void sql_delete();
    void sql_update();
    void sql_select();

private:
    MYSQL m_sql;
};

#endif
