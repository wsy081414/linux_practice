#include"comm.h"
int main()
{
    int shmid=Create_Shm();
    sleep(5);
    char *add=At_Shm(shmid);
    while(1)
    {
        sleep(1);
        printf("%s\n",add);
    }
    sleep(5);
    Dt_Shm(add);
    Destory_Shm(shmid);
    return 0;
}
