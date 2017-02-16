#include<unistd.h>
#include"comm.h"
int main()
{
    int semid=Creat_Sem();
    int ret=Init_Sem(semid);
    if(ret<0)
    {
        return -1;
    }
    printf("semid:%d\n",semid);
    pid_t id=fork();
    if(id==0)
    {
        //child
        while(1)
        {
            P_Sem(semid,0);
            usleep(10002);
            printf("A");
            fflush(stdout);
            usleep(1080);
            printf("A");
            fflush(stdout);
            V_Sem(semid,0);
        }
    }
    else
    {
        while(1)
        {
            P_Sem(semid,0);
            printf("B");
            usleep(10080);
            fflush(stdout);
            printf("B");
            usleep(12000);
            fflush(stdout);
            V_Sem(semid,0);
        }
        wait(NULL);
    }

    Destory_Sem(semid);


    return 0;
}
