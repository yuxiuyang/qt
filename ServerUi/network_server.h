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
class Network_Server
{
public:
    Network_Server();
    ~Network_Server();

    bool init();
    int waitAccept();
    void stop();
    int recvData(int socket,char* buf,int len);
    int sendData(int socket,char* buf,int len);
    int getServerSocketFd(){
        return m_serverSockFd;
    }

private:
    int m_serverSockFd;
    unsigned short m_serverPort;
    struct sockaddr_in m_serverAddress;
};

#endif // NETWORK_SERVER_H
