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
void request_404(int sock)
{
    char buf[1024];

}
void echo_error(int sock, int err_code)
{
    switch(err_code)
    {
        case 401:
        break;
        case 404:
        request_404(sock);
        break;
        case 503:
        break;
        case 500
        break;
        default:
        break;
    }

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
    }while(ret != 1 && strcmp(buf, "\n") != 0);
    return ret;
}

static void echo_www(int sock, char *path, int _s)
{
    int fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        print_log("open failed!", FATAL);
        return ;
    }
    char buf[SIZE];
    sprintf(buf,"HTTP/1.0 200 OK \r\n\r\n");

    printf("buf:%s\n",buf);
    if(send(sock,buf,strlen(buf),0) < 0)
    {
        print_log("send filed",FATAL);
        return;
    }

    if(sendfile(sock, fd, NULL,_s) < 0)
    {
        print_log("sendfile failed",FATAL);
        return ;
    }

    close(fd);
    return;
}

static int excu_cgi(int sock, char *method, char *path, char* query_string)
{
    int ret = 0;
    int content_length = -1;
    if (strcasecmp(method,"GET")==0)
    {
        //GET方法
        clear_header(sock);
        // 此时的query_string就是记录的参数，后期进行使用就好了。
    }else{
        //POST方法，这个时候所需要做的是取出POST的参数，这个POST的参数是在POST的正文处。
        char buf[SIZE];
        memset(buf, 0, sizeof(buf));
        //POST
        do{
            ret = get_line(sock, buf, sizeof(buf));
            if(strncasecmp(buf, "Content-Length: ", strlen("Content-Length: ")))
            {
                content_length = atoi (buf+strlen("content_length: "));
            }

        }while(ret != 1 && strcmp(buf, "\n") != 0);

        
    }//else

    if(content_length < 0)
    {
        return 1;
    }

    char buf[SIZE];
    sprintf(buf,"HTTP/1.0 200 OK \r\n\r\n"); 
    send(sock, buf, strlen(buf), 0);

    int input[2];
    int output[2];

    if(pipe(input) < 0)
    {
        return 2;
    }
    if(pipe(output) < 0)
    {
        return 3;
    }

    pid_t id = fork();
    if(id < 0)
    {
        return 4;
    }
    else if(id == 0){
        //child
        close(input[1]);// 关闭写端
        close(output[0]);//关闭读端

        dup2(input[0], 0);
        dup2(output[1], 1);
        
        char method_env[SIZE/8];
        char content_len[SIZE/8];

        sprintf(method_env,"METHOD=%s", method);
        putenv(method_env);

        if(strcasecmp(method,"GET") == 0)
        {
            sprintf(content_len, "QUERY_STRING=%s", query_string);
            putenv(content_len);
        }
        else{
            sprintf(content_len, "CONTENT_LEN=%d", content_length);
            putenv(content_len);
        }
        execl(path,path,NULL);
        exit(1);
    }//child 
    else{
        //father
        close(input[0]);
        close(output[1]);

        if(strcasecmp(method, "GET") == 0){   
            //GET
        }
        else{
            //POST
            
            char ch;
            int i = 0;
            for(i = 0; i < content_length; i++)
            {
                recv(sock, &ch, 1, 0);
                write(input[1], &ch, 1);
            }

            char ouput_data[SIZE];
            while(read(output[0],&ch,1))
            {
                send(sock, &ch, 1, 0);
            }
        }
        waitpid(id,NULL,0);
    }//father   
}
int handler_sock(int sock)
{
    char buf[SIZE];
    int ret;

    //进行读取一行
    if(get_line(sock, buf, sizeof(buf)) < 0)
    {
        print_log("get_line error",WARNING);
        ret = 6;
    }

    char method[METHOD_SIZE];
    char url[URL_SIZE];

    int i = 0,j = 0;
    
    printf("http:%s\n", buf);

    //进行截取请求方式
    while(i < sizeof(buf)-1 && j<sizeof(method)-1 && !isspace(buf[i]))
    {
        method[j++] = buf[i++];
    }
    
    printf("methed:%s\n",method);
    if(strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        printf("end\n");
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
    char *query_string =NULL;
    printf("url:%s\n",url);
    int cgi=0;
    if(strcasecmp(method,"POST")==0)
    {
        cgi=1;
    }
    if(strcasecmp(method,"GET")==0)
    {
        query_string = url;
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

        char path[SIZE];
        sprintf(path, "wwwroot%s", url);
        if( path[strlen(path)-1] == '/')
        {
            strcat(path,"index.html");
        }

        printf("path:%s\n",path);

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

        printf("path:%s\n",path);
        printf("cgi:%d\n",cgi);
        if (cgi){
            //对于cgi模式，我们需要对参数进行处理,method记录请求方法，path记录了资源路径，query_string记录的是参数。
            ret = excu_cgi(sock, method, path, query_string);

        }//fi
        else{
            //非cgi模式，此时需要把这个HTTP报文进行全部访问完毕，防止出现后续出现以后报文粘包问题。
            printf("echo_www:\n");
            clear_header(sock);
            //接下来进行最简单的非cgi版本的操作，直接把这个资源发送过去。
            echo_www(sock, path, sizeof(path));
        }//else

end:
    close(sock);
    return ret;
}
