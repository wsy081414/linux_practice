#include"comm.h"


int Comm_Shm(int flags)
{
    key_t shmkey=ftok(PATHNAME,PROJID);
    if(shmkey<0)
    {
        perror("ftok");
        return -1;
    }
    printf("sda");

    int shmid=shmget(shmkey,SIZE,flags);
    if(shmget<0)
    {
        perror("shmget");
        return -2;
    }
    printf("create");
    return shmid;
}
int Create_Shm()
{
    return Comm_Shm(IPC_CREAT|IPC_EXCL|0666);
}
int Get_Shm()
{
    return Comm_Shm(0);
}
int Destory_Shm(int shmid)
{
    int ret=shmctl(shmid,IPC_RMID,NULL);
    if(ret<0)
    {
        perror("shmctl");
        return -1;
    }
    return 0;
}

char* At_Shm(int shmid)
{
    char *shm=(char *)shmat(shmid,NULL,0);
    return shm;
}
int Dt_Shm(char *mem_addr)
{
    int ret =shmdt(mem_addr);
    return 0;
}
