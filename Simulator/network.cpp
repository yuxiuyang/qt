#include "network.h"
#include <signal.h>
#include "../include/define.h"
#include <errno.h>
Network::Network()
{
    memset(&m_serverAddress,0,sizeof(m_serverAddress));
    m_serverPort = 8090;

    //忽略SIGPIPE 信号
    signal(SIGPIPE,SIG_IGN);
}
bool Network::init(){
    m_sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == m_sockFd)
    {
        cout<<"socket fail !"<<endl;
        return false;
    }
    bzero(&m_serverAddress,sizeof(struct sockaddr_in));
    m_serverAddress.sin_family=AF_INET;
    m_serverAddress.sin_addr.s_addr= inet_addr("127.0.0.1");
    m_serverAddress.sin_port=htons(m_serverPort);
    //printf("s_addr = %#x ,port : %#x\r\n",m_serverAddress.sin_addr.s_addr,m_serverAddress.sin_port);

    return true;
}

bool Network::connect(){
    init();
    cout<<"connect m_sockFd="<<m_sockFd<<endl;

    if(-1 == ::connect(m_sockFd,(struct sockaddr *)(&m_serverAddress), sizeof(struct sockaddr)))
    {
        //printf("connect fail !\r\n");
        cout<<"connect fail errno="<<errno<<endl;
        return false;
    }
    printf("connect ok !\r\n");
    return true;
}
bool Network::disConnect(){
    close(m_sockFd);
    return true;
}
