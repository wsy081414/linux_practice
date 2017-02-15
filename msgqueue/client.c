#include"comm.h"
int main()
{
    int msqid=getmsg();
    char buf[MYSIZE];
    char out[2*MYSIZE];
    while(1){
        printf("please input:");
        fflush(stdout);

        ssize_t _s=read(0,buf,sizeof(buf)-1);
        if(_s>0)
        {
            buf[_s]='\0';
            sendmsg(msqid,CLIENT_TYPE,buf);
        }
        if(recvmsg(msqid,SERVER_TYPE,out)<0)
        {
            break;
        }
        printf("server echo :%s\n",out);
    }
    
    return 0;

}
