#include"comm.h"
int main()
{
    int msqid=getmsg();
    char buf[MYSIZE];
    char out[2*MYSIZE];
    while(1){
        printf("please input:");
        fflush(stdout);
        //从输入流进行读取输入信息
        ssize_t _s=read(0,buf,sizeof(buf)-1);
        if(_s>0)
        {
            buf[_s]='\0';
            sendmsg(msqid,CLIENT_TYPE,buf);
        }
        //接受服务器发来的消息，如果接受不到，直接推出while循环
        if(recvmsg(msqid,SERVER_TYPE,out)<0)
        {
            break;
        }
        printf("server echo :%s\n",out);
    }
    
    return 0;

}
