/*************************************************************************
	> File Name: sql_api.cpp
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Thu 13 Apr 2017 05:33:47 AM PDT
 ************************************************************************/

#include"sql_api.h"
using namespace std;

sqlopt::sqlopt()
{
    mysql_init(&m_sql);
}
sqlopt::~sqlopt()
{
    mysql_close(&m_sql);
}
int sqlopt::sql_connect()
{
    bool ret = true;
    if(mysql_real_connect(&m_sql,"localhost","root","111","s_info",3306,NULL,0 ));
    {
        cerr<<"real_connect";
        ret =false;
    }
    cout<<"connect"<<endl;
    return ret;
}
int sqlopt::sql_insert(const string& data)
{
    string sqldata = "insert into s_info(name,sex,age,school)values(";
    sqldata += data;
    sqldata +=")";
    mysql_query(&m_sql,sqldata.c_str());
}
void sqlopt::sql_delete()
{
    
}
void sqlopt::sql_update()
{
    
}
void sqlopt::sql_select()
{
//    MYSQL_RES *res; 
//
//    string sqlselect = "select * from s_info";
//    if(mysql_query(&m_sql, sqlselect.c_str()) == 0)
//    {
//        res = mysql_store_result(&m_sql);
//        int rows = mysql_num_rows(res);
//        int fields = mysql_num_fields(res);
//
//        int  i = 0 ;
//        MYSQL_ROW line;
//        for(int i =0; i<rows; i++)
//        {
//            line = mysql_fetch_row(res);
//            int j = 0;
//            for(;j < fields; ++j)
//            {
//                cout<<line[j]<<" "
//            }
//            cout<<endl;
//        }
//    }
}
