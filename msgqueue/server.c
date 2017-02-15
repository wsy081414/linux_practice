#include"comm.h"
int main()
{
    int msqid=createmsg();
    char buf[2*MYSIZE];
    while(1){
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
