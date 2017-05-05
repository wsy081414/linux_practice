/*************************************************************************
	> File Name: cgi_math.c
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sat 08 Apr 2017 12:53:24 AM PDT
 ************************************************************************/

#include"sql_api.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define SIZE 4096
int main()
{
    char method[SIZE];
    char content_data[SIZE];
    memset(method,0,sizeof(method));
    memset(content_data, 0 ,sizeof(content_data));
    int content_length = -1;
    
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
            memset(len,0,sizeof(len));
            strcpy(len,getenv("CONTENT_LEN"));
            content_length = atoi(len);
            int i = 0;
            char ch = 0;
            for( ; i < content_length; i++)
            {
                read(0,&ch,1);
                content_data[i]=ch;
            }
            content_data[i] = '\0';
        }
        else{
            return 3;
        }
    }//POST
    

    //到这里以后，就可以确定此时我的content_length当中已经保留了需要的参数。
    char *arr[5];
    int i = 0;
    int j = 0;
    char *string_start = content_data;
    int size=strlen(content_data);
    for(i =0; i < size; i++)
    {
        if(*string_start == '=')
        {
            string_start++;
            arr[j] = string_start;
            j++;
        }else if(*string_start == '&')
        {
            *string_start = '\0';
        }
        else{}
        string_start++;
    }
    arr[4] = NULL;
    string data = "";
    int n=5;
    for(int j=0; j<n; j++)
    {
        if(j == 2)
        {
            data +=arr[j];
            data +=",";
            continue;
        }

        if(j == n-1)
            break;
        data+="\'";
        data+=arr[j];
        data+="\'";
        if(j < n-2)
            data +=",";
    }


    sqlopt a;
    a.sql_connect();
    a.sql_select(data);


   //int data1 = atoi(arr[0]);
    //int data2 = atoi(arr[1]);
    //
    //printf("<h1>%d + %d = %d</h1><br/>\n",data1,data2,data1+data2);
    //printf("<h1>%d - %d = %d</h1><br/>\n",data1,data2,data1-data2);
    //printf("<h1>%d * %d = %d</h1><br/>\n",data1,data2,data1*data2);
    //printf("<h1>%d / %d = %d</h1><br/>\n",data1,data2,data1/data2);
    //printf("<h1>%d %% %d = %d</h1><br/>\n",data1,data2,data1%data2);
    //printf("</html>");
}
