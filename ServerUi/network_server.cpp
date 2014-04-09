#include "network_server.h"
#include <assert.h>
#include <iostream>
#include <signal.h>
using namespace std;

Network_Server::Network_Server()
{
    m_serverSockFd = -1;
    m_serverPort = 8090;

    //忽略SIGPIPE 信号
    signal(SIGPIPE,SIG_IGN);
}
Network_Server::~Network_Server()
{
    stop();
}
bool Network_Server::init(){
    //return true;
    printf("Hello,welcome to my server !\r\n");
    m_serverSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == m_serverSockFd)
    {
        printf("socket fail ! \r\n");
        return false;
    }
    printf("socket ok !\r\n");


    bzero(&m_serverAddress,sizeof(struct sockaddr_in));
    m_serverAddress.sin_family=AF_INET;
    m_serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
    m_serverAddress.sin_port=htons(m_serverPort);

    if(-1 == bind(m_serverSockFd,(struct sockaddr *)(&m_serverAddress), sizeof(struct sockaddr)))
    {
        printf("bind fail !\r\n");
        return false;
    }
    printf("bind ok !\r\n");

    if(-1 == listen(m_serverSockFd,5))
    {
        printf("listen fail !\r\n");
        return false;
    }
    printf("listen ok\r\n");
    return true;
}
int Network_Server::waitAccept(){
    if(m_serverSockFd==-1){
        cout<<"please init server first"<<endl;
        return -1;
    }
    struct sockaddr_in client_addr;
    socklen_t addrLen=sizeof(struct sockaddr_in);
    return accept(m_serverSockFd, (struct sockaddr *)(&client_addr), &addrLen);
}
void Network_Server::stop(){
    if(m_serverSockFd != -1){
        cout<<"close server socket="<<m_serverSockFd<<endl;
        close(m_serverSockFd);
    }
}

int Network_Server::recvData(int socket,Msg_* msg){
    assert(msg);
    return recv(socket,msg,sizeof(Msg_), 0);
}
int Network_Server::sendData(int socket,const Msg_* msg){

    int len = sizeof(Msg_);
    int total = 0;
    while(1){
        int size = send(socket,msg,len,0);
        if(size<=0){
            printf("send error errno=%d\n",errno);
            return size;
        }
        total += size;
        if(size<len){
            len -= size;
            continue;
        }else{
            break;
        }
    }
    return total;
}
