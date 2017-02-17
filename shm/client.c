#include"comm.h"
int main()
{
    int shmid=Get_Shm();

    char *add=At_Shm(shmid);
    
    printf("physic address:%s",add);
    int i=0;
    while(1)
    {
        sleep(1);
        add[i++] = 'a';
        i %= (SIZE-1);
        add[i]='\0';

    }
    Dt_Shm(add);
    return 0;
}
