#include"comm.h"



int Init_Sem(int semid)
{
    union semun {
        int              val;    /* Value for SETVAL */
        struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
        unsigned short  *array;  /* Array for GETALL, SETALL */
        struct seminfo  *__buf;  /* Buffer for IPC_*/       
    };

    union semun semun;
    semun.val=1;
    int ret=semctl(semid,0,SETVAL,semun);
    if(ret<0)
    {
        perror("semctl");
        return -1;
    }
    return ret;
} 
static int Comm_Sem(int flags,int nsems)
{
    key_t semkey=ftok(PATHNAME,PROJID);
    if(semkey<0)
    {
        perror("ftok");
        return -1;
    }
    int semid=semget(semkey,nsems,flags);
    if(semid<0)
    {
        perror("semget");
        return -2;
    }
    return semid;
}
int Creat_Sem()
{
    return Comm_Sem(IPC_CREAT|IPC_EXCL|0666,1);
}
int Get_Sem()
{
    return Comm_Sem(IPC_CREAT,0);
}
int Destory_Sem(int semid)
{
    int ret=semctl(semid,0,IPC_RMID); 
}

static int Comm_Op(int semid,int which,int op)
{
    struct sembuf sembuf;
    sembuf.sem_num=which;
    sembuf.sem_op=op;
    sembuf.sem_flg=0;

    int ret=semop(semid,&sembuf,1);
    if(ret<0)
    {
        perror("semop");
        return -1;
    }
    return ret;
}
int P_Sem(int semid,int which)
{
    return Comm_Op(semid,which,-1);
}
int V_Sem(int semid,int which)
{
    return Comm_Op(semid,which,1);
}
