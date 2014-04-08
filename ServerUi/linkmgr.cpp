#include "linkmgr.h"
#include <errno.h>
LinkMgr* LinkMgr::m_instance = new LinkMgr();
LinkMgr::LinkMgr(QObject *parent) :
    QThread(parent)
{
    m_initServerOk = m_serverNetwork.init();
    m_maxClientFd = m_serverNetwork.getServerSocketFd();
    m_window = NULL;
}

LinkMgr::~LinkMgr(){
    assert(m_instance);
}

LinkMgr* LinkMgr::getInstance(){
    return m_instance;
}

void LinkMgr::run(){
    if(!m_initServerOk){
        cout<<"please init server first   thread run failure"<<endl;
        return;
    }
    fd_set fdSet;
    int clientFd=-1;
    int ret = -1;
    struct timeval tv;
    char recvBuf[MAX_RECIEVE_BUF];
    char msgBuf[200]={0};
    while(1){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        FD_SET(m_serverNetwork.getServerSocketFd(), &fdSet);

        // timeout setting
       tv.tv_sec = 30000;
       tv.tv_usec = 0;

        // add active connection to fd set
        std::map <int, Link*>::iterator iter;
        for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
            cout<<"add fd ="<<iter->first<<endl;
            FD_SET(iter->first, &fdSet);
        }

        ret = select(m_maxClientFd + 1, &fdSet, NULL, NULL, &tv);
        if (ret < 0) {
            printf("select error\n");
            ((MainWindow*)m_window)->appendMsg("select error");
            break;
        } else if (ret == 0) {
            printf("timeout\n");
            ((MainWindow*)m_window)->appendMsg("timeout");
            continue;
        }
        ((MainWindow*)m_window)->appendMsg("select success");
        // check every active client fd in the set
        std::map <int, Link*>::iterator iter1;
        for(iter1=m_clientConnectMsgMap.begin();iter1!=m_clientConnectMsgMap.end();iter1++){
            if (FD_ISSET(iter1->first, &fdSet)) {
                cout<<"iter1->first="<<iter1->first<<endl;
                memset(recvBuf,0,sizeof(recvBuf));
                ret = m_serverNetwork.recvData(iter1->first,recvBuf,sizeof(recvBuf));
                if (ret <= 0) {        // client close
                    printf("clientfd=%d close ret=%d,errno=%d\n", iter1->first,ret,errno);
                    close(iter1->first);
                    FD_CLR(iter1->first, &fdSet);
                    removeClientSocket(iter1->first);
                } else {        // receive data
                    if (ret < sizeof(recvBuf)){
                       recvBuf[ret]='\0';
                       ((MainWindow*)m_window)->appendMsg(recvBuf);
                       //memset(&recvBuf[ret], '\0', 1);
                    }
                    else{
                       printf("maybe recv buf len is too small\n");
                    }
                }
            }
        }


        //check serversocket is connected by other client
        if (FD_ISSET(m_serverNetwork.getServerSocketFd(), &fdSet)) {
            cout<<"start listen"<<endl;
            clientFd = m_serverNetwork.waitAccept();
            if(-1 == clientFd){
                cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
                if(EAGAIN == errno){

                }
                //continue;
            }

            //manage client FD
            if(!findClient(clientFd)){// not exsit
                std::pair< std::map< int, Link* >::iterator, bool> ct;
                ct = m_clientConnectMsgMap.insert( std::pair <int, Link*> ( clientFd,  NULL) );
                if( ct.second ){
                    //printf("\n m_Event_Name_Map insert Data Success....m,size=%d,this=%lu\n",m_clientConnectMsgMap.size(),this);
                    sprintf(msgBuf,"accept client =%d success",clientFd);
                    ((MainWindow*)m_window)->appendMsg(msgBuf);
                    if(m_maxClientFd<clientFd){
                        m_maxClientFd = clientFd;
                    }
                }else{
                     printf("\n m_Event_Name_Map insert Data fail....\n");
                }
            }else{
                cout<<"this client="<<clientFd<<"has exist"<<endl;
            }

            cout<<"accept socket success socket="<<clientFd<<endl;
            //sysn socket
            assert(sendToClient(clientFd));//
       }

    }
}
bool LinkMgr::registerSocketFd(int socketFd){
    if(isRegister(socketFd))
        return false;
    m_registerClientSocketFdVec.push_back(socketFd);
    return true;
}

bool LinkMgr::unregisterSocketFd(int socketFd){
    vector<int>::iterator iter=find(m_registerClientSocketFdVec.begin(),m_registerClientSocketFdVec.end(),socketFd);
    if(iter == m_registerClientSocketFdVec.end()){
        cout<<"has not register sockFd="<<socketFd<<endl;
        return false;
    }

    m_registerClientSocketFdVec.erase(iter);
    return true;
}
bool LinkMgr::isRegister(int socketFd){//check weather has register
    vector<int>::iterator iter=find(m_registerClientSocketFdVec.begin(),m_registerClientSocketFdVec.end(),socketFd);
    if(iter==m_registerClientSocketFdVec.end()){
        cout<<"this socketFd="<<socketFd<<"has exist"<<endl;
        return true;
    }
    return false;
}
bool LinkMgr::sendToClient(int clientSocket){//send connect or disconnect to client
    return true;
}

Link* LinkMgr::findClient(int clientSocket){
    std::map <int, Link*>::iterator iter;
    iter = m_clientConnectMsgMap.find(clientSocket);//search clientFd

    return iter==m_clientConnectMsgMap.end()?NULL:iter->second;
}
int LinkMgr::getMaxClientFd(){
//    std::map <int, Link*>::iterator iter;
//    for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
//        if(m_maxClientFd<iter->first){
//            m_maxClientFd = iter->first;
//        }
//    }
    return m_maxClientFd;
}
bool LinkMgr::removeClientSocket(int clientSocket){
    std::map <int, Link*>::iterator iter;
    iter = m_clientConnectMsgMap.find(clientSocket);//search clientFd

    if(iter != m_clientConnectMsgMap.end()){
        m_clientConnectMsgMap.erase(iter);

        unregisterSocketFd(clientSocket);
        return true;
    }

    printf("has not exist\n");
    return false;

}
void LinkMgr::setWindow(void* win){
    m_window = win;
}
