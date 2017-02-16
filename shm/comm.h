#ifndef __COMM_H_
#define __COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
#define PROJID 0x6666
#define SIZE 4096*1

int Comm_Shm(int flags);
int Create_Shm();
int Get_Shm();
int Destory_Shm(int shmid);
char *At_Shm(int shmid);
int Dt_Shm(char *mem_addr);



#endif //!__COMM_H_
