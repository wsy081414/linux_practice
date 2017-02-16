#include"comm.h"
int main()
{
    int shmid=Create_Shm();

    sleep(9);
    char *shm=At_Shm(shmid);
    sleep(5);
    Dt_Shm(shm);
    sleep(5);
    Destory_Shm(shmid);
    return 0;
}
