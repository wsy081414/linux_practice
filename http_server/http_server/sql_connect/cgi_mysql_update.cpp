/*************************************************************************
	> File Name: cgi_math.c
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sat 08 Apr 2017 12:53:24 AM PDT
 ************************************************************************/

#include"sql_api.h"
#include<stdlib.h>
#include<string.h>
#define SIZE 4096
int main()
{
    char method[SIZE];
    char content_data[SIZE];
    int content_length = -1;
    
    memset(content_data, 0, SIZE);
    if(getenv("METHOD"))
    {
        strcpy(method, getenv("METHOD"));
    }
    else{
        //错误处理
        return 1;
    }
    

    if(strcasecmp(method, "GET") == 0)
    {
        if(getenv("QUERY_STRING"))
        {
            strcpy(content_data,getenv("QUERY_STRING"));
        }
        else{
            return 2;
        }
    }//GET
    else{
        if(getenv("CONTENT_LEN"))
        {
            char len[SIZE];
            strcpy(len,getenv("CONTENT_LEN"));
            content_length = atoi(len);
            read(0,content_data,content_length);
        }
        else{
            return 3;
        }
    }//POST
    

    //到这里以后，就可以确定此时我的content_length当中已经保留了需要的参数。

    char *arr[3];
    int i = 0;
    int j = 0;
    char *string_start = content_data;
    int size=strlen(content_data);

    
    for( i = 0;i<size;i++)
    {
        if(*string_start == '=')
        {
            arr[j++]=string_start+1;
        }
        else if(*string_start == '&')
        {
            *string_start = '\0';
        }
        string_start++;
    }

    arr[2] = NULL;
    string data="";

    data+="sex='";
    data+=arr[0];
    data+="' where id=";
    data+=arr[1];

    sqlopt a;
    a.sql_connect();
    a.sql_update(data);
    a.sql_select(data);


    //int data1 = atoi(arr[0]);
    //int data2 = atoi(arr[1]);
    //
    //printf("<html>\n");
    //printf("<h1>%d + %d = %d</h1><br/>\n",data1,data2,data1+data2);
    //printf("<h1>%d - %d = %d</h1><br/>\n",data1,data2,data1-data2);
    //printf("<h1>%d * %d = %d</h1><br/>\n",data1,data2,data1*data2);
    //printf("<h1>%d / %d = %d</h1><br/>\n",data1,data2,data1/data2);
    //printf("<h1>%d %% %d = %d</h1><br/>\n",data1,data2,data1%data2);
    //printf("</html>");
}
