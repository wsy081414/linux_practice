/*************************************************************************
> File Name: udpServer.cpp
> Author:yuzhe 
> Mail:953659912@qq.com 
> Created Time: Sun 23 Apr 2017 01:17:12 AM PDT
************************************************************************/

#include<iostream>
using namespace std;

udpServer::udpServer(const int &port,const string &ip)
:_port(port)
,_ip(ip)
{
}
udpServer::~udpServer()
{
    close(_sock);
}
int udpServer::recvData(string &instring)
{
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);

    ssize_t _s = recvfrom(_sock , instring.c_str(), sizeof(instring), 0, (struct sockaddr *)&remote , &len);
    if(_s > 0 )
    {
        addUser(remote);
        putData(instring);
    }
    return _s;
}
int udpServer::sendData(const string &outstring,struct sockaddr_in &remote)
{
    ssize_t _s = sendto(_scok, outstring.c_str(), outstring.size(), 0,(struct sockaddr *)&remote , sizeof(remote));
    if(_s < 0)
    {

    }
    return _s
}
int udpServer::udpServerInit()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        //print_log
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(_port);
    local.sin_addr.s_addr = inet_addr(_ip.c_str());

    if(bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
    {
        //print_log
        exit(2);
    }
    return sock;
}
void udpServer::broadCast()
{
    string outstring ;
    getData(outstring);
    auto it = userList.begin();
    for(;it != userList.end(); it++)
    {
        sendData(outstring, it->second);
    }
}
void udpServer::addUser(struct sockaddr_in& remote)
{
    map.insert(std::pair<be32 , sockaddr_in>(remote.sin_addr.s_addr, remote));
}
