#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

#define PATHNAME "."
#define PROJID 0x6666

int Init_Sem(int semid);
int Get_Sem();
int Creat_Sem();
int Destory_Sem(int semid);
int P_Sem(int semid,int which);
int V_Sem(int semid,int which);


#endif //!__COMM_H__

