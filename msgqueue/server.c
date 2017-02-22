#include"comm.h"
int main()
{
    //创建消息队列
    int msqid=createmsg();
    char buf[2*MYSIZE];
    while(1){
        //接收消息，如果缓冲区接受不到，退出循环，否则打印
        if(recvmsg(msqid,CLIENT_TYPE,buf)<0)
        {
            break;
        }
        printf("client# %s\n",buf);
        if(sendmsg(msqid,SERVER_TYPE,buf)<0)
        {
            break;   
        }
    }
    destorymsg(msqid);
    
    return 0;
}
