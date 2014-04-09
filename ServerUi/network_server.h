#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include "../include/define.h"
class DataDev;
class Network_Server
{
public:
    Network_Server();
    ~Network_Server();

    friend class DataDev;

protected:
    bool init();
    int waitAccept();
    void stop();
    int recvData(int socket,Msg_* msg);
    int sendData(int socket,const Msg_* msg);
    int getServerSocketFd(){
        return m_serverSockFd;
    }
private:
    int m_serverSockFd;
    unsigned short m_serverPort;
    struct sockaddr_in m_serverAddress;


};

#endif // NETWORK_SERVER_H
