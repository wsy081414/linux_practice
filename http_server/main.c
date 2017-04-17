#include"httpd.h"
static void *accept_request(void * arg)
{
    int sock = (int )arg;
    pthread_detach(pthread_self());

    return (void *)handler_sock(sock);
}
int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s [local_ip] [local_port]\n", argv[0]);
        return 1;
    }
    int listen_sock = startup(argv[1],atoi(argv[2]));
    
    //int _r = daemon(1,0);

    while(1)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);

        int sock = accept(listen_sock, (struct sockaddr *)&peer, &len);
        if(sock < 0)
        {
            print_log("accept failed",WARNING);
            continue;
        }

        pthread_t tid;

        pthread_create(&tid, NULL, accept_request, (void *)sock );
    }


    return 0;
}
