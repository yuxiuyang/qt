#ifndef LINKMGR_H
#define LINKMGR_H

#include <QThread>
#include "../include/link.h"
#include "network_server.h"
#include<algorithm>
#include <map>
#include <vector>
#include "mainwindow.h"
using namespace std;
#define MAX_RECIEVE_BUF 1024

class LinkMgr : public QThread
{
Q_OBJECT
private:
    explicit LinkMgr(QObject *parent = 0);
public:
    virtual ~LinkMgr();
signals:

public slots:


public:
    virtual void run();

    static LinkMgr* getInstance();
    static LinkMgr* m_instance;

    bool registerSocketFd(int socketFd);
    bool unregisterSocketFd(int socketFd);

    bool sendToClient(int clientSocket);//send connect or disconnect to client

    Link* findClient(int clientSocket);
    bool removeClientSocket(int clientSocket);
    int getMaxClientFd();
    void setWindow(void* win);
private:
    Network_Server m_serverNetwork;
    bool m_initServerOk;

    map<int,Link*> m_clientConnectMsgMap;
    vector<int> m_registerClientSocketFdVec;
    bool isRegister(int socketFd);//check weather has register

    int m_maxClientFd;


    void* m_window;
};

#endif // LINKMGR_H
