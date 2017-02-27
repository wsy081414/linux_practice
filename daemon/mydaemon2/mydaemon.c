#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>
void mydaemon()
{
    //设置掩码
    umask(0);

    //父进程进行退出
    if(fork()>0)
    {
        exit(2);
    }
    //创建新的会话
    setsid();
    
    //捕捉SIGCHLD信号，操作为忽略
    signal(SIGCHLD,SIG_IGN);

    //进行第二次fork()，为了防止新的紫禁城再次进行调用控制终端
    if(fork()>0)
    {
        exit(2);   
    }

    //改变文件目录
    chdir("/");
    //关闭文件描述符
    close(0);
    close(1);
    close(2);

}
int main()
{
    mydaemon();
    while(1)
    {

    }
    return 0;
}
