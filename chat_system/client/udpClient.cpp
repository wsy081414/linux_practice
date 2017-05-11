/*************************************************************************
> File Name: udpClient.cpp
> Author:yuzhe 
> Mail:953659912@qq.com 
> Created Time: Sun 23 Apr 2017 01:17:12 AM PDT
************************************************************************/

#include<iostream>
using namespace std;

udpClient::udpClient(const int &port,const string &ip)
:_port(port)
,_ip(ip)
{
}
udpClient::~udpClient()
{
    close(_sock);
}
int udpClient::recvData(string &instring)
{
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);
    char buf[1024];
    ssize_t _s = recvfrom(_sock , buf, sizeof(buf), 0, (struct sockaddr *)&remote , &len);
    if(_s > 0 )
    {
        buf[_s] = '\0';
        instring = buf;
        addUser(remote);
        putData(instring);
    }
    return _s;
}
int udpClient::sendData(const string &outstring,struct sockaddr_in &remote)
{
    ssize_t _s = sendto(_scok, outstring.c_str(), outstring.size(), 0,(struct sockaddr *)&remote , sizeof(remote));
    if(_s < 0)
    {
        //print_log
    }
    return _s
}
int udpClient::udpClientInit()
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
void udpClient::broadCast()
{
    string outstring ;
    getData(outstring);
    auto it = userList.begin();
    for(;it != userList.end(); it++)
    {
        sendData(outstring, it->second);
    }
}
void udpClient::addUser(struct sockaddr_in& remote)
{
    userList.insert(std::pair<be32 , sockaddr_in>(remote.sin_addr.s_addr, remote));
}
