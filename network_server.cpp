#include "network_server.h"

Network_Server::Network_Server(QObject *parent) :
    QThread(parent)
{
    m_serverSockFd = -1;
    m_serverPort = 8090;
}
Network_Server::~Network_Server()
{
    if(m_serverSockFd != -1){
        close(m_serverSockFd);
    }
}
bool Network_Server::init(){
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

void Network_Server::startServer(){
    if(m_serverSockFd==-1)
        return;

   struct sockaddr_in client_addr;
    int clientFd=-1;
    socklen_t sin_size=-1;
    char buf[300]={0};
    while(1)
    {
        sin_size = sizeof(struct sockaddr_in);

        clientFd = accept(m_serverSockFd, (struct sockaddr *)(&client_addr), &sin_size);
        if(-1 == clientFd)
        {
            printf("accept fail !\r\n");
            return ;
        }
        sprintf(buf,"accept ok!,clientFd=%d\r\nServer start get connect from %#x : %#x\r\n",clientFd,ntohl(client_addr.sin_addr.s_addr),ntohs(client_addr.sin_port));
        cout<<buf;
//        if(-1 == write(clientFd,"hello,welcome to my server \r\n",32))
//        {
//            printf("write fail!\r\n");
//            return ;
//        }
//        printf("write ok!\r\n");
        close(clientFd);

    }
}
void Network_Server::stopServer(){

}

void Network_Server::run(){
    startServer();
}
