#ifndef LINKMGR_H
#define LINKMGR_H

#include "../include/define.h"
#include<algorithm>
#include <map>
#include <vector>
#include "network_server.h"
using namespace std;
#define MAX_RECIEVE_BUF 1024

class LinkMgr
{
public:
    LinkMgr();
    virtual ~LinkMgr();
    
    void* m_window;

public:
    bool registerSocketFd(int socketFd);
    bool unregisterSocketFd(int socketFd);

    bool sendToClient(int clientSocket);//send connect or disconnect to client

    Link* findClient(int clientSocket);
    bool removeClientSocket(int clientSocket);
    void setWindow(void* win);
    void getClientSocketFd(int clientFd[],int& len);
    void getClientSocketFd(vector<int>* vec);
    bool addClientSocketFd(int clientFd);
    void recvLinkMsg(CONNECT_MSG_TYPE type,int clientFd,int error=-1);
    void recvLinkMsg(const Link* linkMsg);

    //accept client connect
    void waitAcceptConnect();

    int getServerFd();


    int findIdentifyForwardFd(LinkSource_ source,ClientType_ type);//find Forwarded object
private:
    map<int,Link*> m_clientConnectMsgMap;
    vector<int> m_registerClientSocketFdVec;
    bool isRegister(int socketFd);//check weather has register

    Network_Server m_serverNetwork;
    bool m_initServerOk;
};

#endif // LINKMGR_H
