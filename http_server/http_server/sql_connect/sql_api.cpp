/*************************************************************************
	> File Name: sql_api.cpp
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Thu 13 Apr 2017 05:33:47 AM PDT
 ************************************************************************/

#include"sql_api.h"

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
    if(mysql_real_connect(&m_sql, "127.0.0.1", "root","111","http_server", 3306, NULL,0 ) == NULL)
    {
        cout<<"real_connect failed"<<endl;
        ret =false;
        goto end;
    }
    
end:
    return ret;
}
int sqlopt::sql_insert(const string& data)
{
    string sqldata = "insert into s_info(name,sex,age,school)values(";
    sqldata += data;
    sqldata +=");";
    mysql_query(&m_sql,sqldata.c_str());
}
void sqlopt::sql_delete(const string& data)
{
    string sqldata = "delete from s_info where id=";
    sqldata += data;
    sqldata += ";";
    mysql_query(&m_sql, sqldata.c_str());
}
void sqlopt::sql_update(const string &data)
{
    string sqldata = "update s_info set ";
    sqldata += data;
    sqldata += ";";
    cout<<sqldata<<endl;
    mysql_query(&m_sql, sqldata.c_str());
}
void sqlopt::sql_select(const string& data)
{
    MYSQL_RES *res; 

    string sqlselect = "select * from s_info";
    if(mysql_query(&m_sql, sqlselect.c_str()) == 0)
    {
        res = mysql_store_result(&m_sql);
        int rows = mysql_num_rows(res);
        int fields = mysql_num_fields(res);

        int  i = 0 ;
        MYSQL_ROW line;
        for(int i =0; i<rows; i++)
        {
            line = mysql_fetch_row(res);
            int j = 0;
            for(;j < fields; ++j)
            {
                cout.setf(ios::left);
                cout.width(9);
                cout<<line[j]<<" ";
            }
            cout<<endl;
        }
    }
}
