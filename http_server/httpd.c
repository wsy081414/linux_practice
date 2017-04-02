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
        exit(3);  
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
        return -1;
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

int handler_sock(int sock)
{
    char buf[SIZE];
    if(get_line(sock, buf, sizeof(buf)) < 0)
    {
        print_log("get_line error",WARNING);
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
    }


end:
    close(sock);

    return 1;
}
