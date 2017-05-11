/*************************************************************************
	> File Name: udpServer.h
	> Author:yuzhe 
	> Mail:953659912@qq.com 
	> Created Time: Sun 23 Apr 2017 01:17:34 AM PDT
 ************************************************************************/

#ifndef _UDPSERVER_H
#define _UDPSERVER_H

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>
#include<map>
#include"log.h"

class udpServer
{
public:
    udpServer(const int &port,const string &ip);
    ~udpServer();
    int recvData(string &instring);
    int sendData(const string &outstring, struct sockaddr_in &remote);
    void broadCast();
private:
    int udpServerInit();
    void addUser(struct sockaddr_in& remote);
private:
    int _sock;
    string _ip;
    int _port;
    map<be32,struct sockaddr_in> userList;
};


#endif
