
#include"comm.h"

static int commmsg(int msgflg)
{
    key_t key=ftok(FILEPATH,PROJID);
    if(key<0)
    {
       perror("ftok");
        return -1;
    }
    int msqid=msgget(key,msgflg);
    if(msqid<0)
    {
        perror("msgget");
        return -2;
    }
    return msqid;
}
int createmsg()
{
    return commmsg(IPC_CREAT|IPC_EXCL|PERM);   
}
int getmsg()
{
    return commmsg(0);
}
int sendmsg(int msgid,long type,const char *msg)
{
    struct msgbuf buf;

    buf.mtype=type;
    strcpy(buf.mtext,msg);

    int id=msgsnd(msgid,&buf,sizeof(buf.mtext),0);
    if(id<0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}
int recvmsg(int msgid,int type,char out[])
{
    struct msgbuf buf;
    int size=msgrcv(msgid,&buf,sizeof(buf.mtext),type,0);
    if(size>0)
    {
        //buf.mtext[size]='\0';
        strncpy(out,buf.mtext,size);
        return 0;

    }
    perror("msgrcv");
    return -1;
}
int destorymsg(int msgid)
{
    if(msgctl(msgid,IPC_RMID,NULL)<0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}

