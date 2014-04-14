#ifndef NETWORK_H
#define NETWORK_H
#include "netdev.h"
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "../include/define.h"
class Network : public NetDev
{
public:
    Network();

public:
    bool init();
    bool connect();
    bool disConnect();

    int recvData(int socket,Msg_* msg);
    int sendData(int socket,const Msg_* msg);
    int sendData(int socketFd,const char* buf,int len);
private:
    struct sockaddr_in m_serverAddress;
    unsigned short m_serverPort;
};

#endif // NETWORK_H
