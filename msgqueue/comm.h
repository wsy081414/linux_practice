#ifndef __COMM_H__
#define __COMM_H__
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<string.h>
#include<time.h>

#define _MSG_SIZE_ 1024
#define FILEPATH "."
#define PROJID 0
#define PERM 0666
#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define MYSIZE 128

struct msgbuf
{
    long mtype;
    char mtext[MYSIZE];
};

static int commmsg(int msgflg);
int createmsg();
int sendmsg(int msgid,long type,const char * msg);
int getmsg();
int recvmsg(int msgid,int type,char out[]);
int destorymsg(int msgid);

#endif //!__COMM_H__
