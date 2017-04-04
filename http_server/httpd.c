#include"httpd.h"


int startup(const char *_ip, int _port)
{

    assert(_ip);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        print_log("socket failed",FATAL);
        exit(2);
    }
    
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(_ip);
    local.sin_port = htons(_port);

    if(bind( sock,(struct sockaddr *)&local, sizeof(local) ) < 0)
    {
        print_log("bind failed",FATAL);
        exit(3);
    }

    if( listen(sock, 5) < 0)
    {
        print_log("listen failed",FATAL);
        exit(4);  
    }

    return sock;
}


void print_log(char *log_massage,int level)
{
    char *arr[10]={
        "NORMAL",
        "WARNING",
        "FATAL"
    };
    #ifdef __debug__
        printf("%s ,%s ",log_massage,arr[level]);
    #endif 
}

static int get_line(int sock, char * buf, int len)
{
    assert(buf);
    if(len < 0)
        return 5;
    char ch='\0';
    int i = 0;

    while(i < len -1 && ch != '\n' )
    {
        if(recv(sock, &ch, 1, 0) > 0)
        {
            //如果字符为\r,此时就是需要处理\n的问题了。

            if(ch == '\r')
            {
                //考虑下一个字符是否为\n
                if( recv(sock, &ch, 1, MSG_PEEK) > 0 && ch == '\n' )
                    recv(sock, &ch, 1, 0);
                else
                    ch = '\n';
            }
            buf[i++] = ch;
        }
        else
            ch = '\n';
    }
    buf[i] = '\0';
    return i;
}
static int clear_header(int sock)
{
    char buf[SIZE];
    int ret = -1;
    do{
        ret = get_line(sock,buf,sizeof(SIZE));
    }while(ret != 1 && strcmp(buf, "\n") != 0)
    return ret;
}
int handler_sock(int sock)
{
    char buf[SIZE];
    int ret;
    if(get_line(sock, buf, sizeof(buf)) < 0)
    {
        print_log("get_line error",WARNING);
        ret = 6;

    }

    char method[METHOD_SIZE];
    char url[URL_SIZE];

    int i,j;

    while(i<sizeof(buf)-1 && j<sizeof(method)-1 && !isspace(buf[i]))
    {
        method[j++] = buf[i++];
    }

    if(strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        //echo_error();
        goto end;
    }

    if(isspace(buf[i]) && i<sizeof(buf)-1)
    {
        i++;
    }

    j = 0;

    while(j < sizeof(url)-1 && i < sizeof(buf)-1 && !isspace(buf[i]))
    {
        url[j++]=buf[i++];
    }
    
    int cgi;
    if(strcasecmp(method,"POST")==0)
    {
        cgi=1;
    }
    if(strcasecmp(method,"GET")==0)
    {
        char *query_string = url;
        while(*query_string != '?' && *query_string != '\0')
        {
            query_string++;
        }
        if(*query_string == '?')
        {
            *query_string = '\0';
            query_string++;
            cgi=1;
        }


        char path[SIZE];
        sprintf(path, "wwwroot%s", url);
        if( path[strlen(path)-1] == '/')
        {
            strcat(path,"index.html");
        }

        struct stat ispath;

        if(stat(path,&ispath) < 0)
        {
            print_log("stat failed",FATAL);
            //echo_error
            goto end;
        }
        else {
            if ( ispath.st_mode & S_IFDIR )
            {
                strcat(path,"/index.html");
            }
            else if((ispath.st_mode & S_IXUSR)|| \
                   (ispath.st_mode & S_IXGRP)|| \
                   (ispath.st_mode & S_IXOTH))
            {
                cgi = 1;
            }
        }

        if (cgi){

        }//fi
        else{
            //非cgi模式，此时需要把这个HTTP报文进行全部访问完毕，防止出现后续出现以后报文粘包问题。

            clear_header(sock);
            //接下来进行最简单的非cgi版本的操作，直接把这个资源发送过去。
            echo_www(sock, path, _s);
        }//else


end:
    close(sock);
    return ret;
}
