#include "linkmgr.h"
#include <errno.h>
#include "mainwindow.h"
LinkMgr::LinkMgr(){
    m_window = NULL;
    m_initServerOk = m_serverNetwork.init();

    //start listen server
    assert(m_initServerOk);
    DataDev::getInstance()->addFd(getServerFd());
}
LinkMgr::~LinkMgr(){
    m_clientConnectMsgVec.clear();
    m_registerClientSocketFdVec.clear();

}
int LinkMgr::getServerFd(){
    return m_serverNetwork.getServerSocketFd();
}
void LinkMgr::waitAcceptConnect(){
    int clientFd = m_serverNetwork.waitAccept();
    if(-1 == clientFd){
        cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
        recvLinkMsg(Connect_Failure,-1,errno);
        if(EAGAIN == errno){

        }
        return;
    }
    recvLinkMsg(Connect_Success,clientFd);

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

bool LinkMgr::findClient(int clientSocket){
    std::vector <int>::iterator iter;
    iter = find(m_clientConnectMsgVec.begin(),m_clientConnectMsgVec.end(),clientSocket);//search clientFd

    return iter==m_clientConnectMsgVec.end()?false:true;
}

bool LinkMgr::removeClientSocket(int clientSocket){
    std::vector <int>::iterator iter;
    iter = find(m_clientConnectMsgVec.begin(),m_clientConnectMsgVec.end(),clientSocket);//search clientFd

    if(iter != m_clientConnectMsgVec.end()){
        DataDev::getInstance()->removeFd(clientSocket);
        m_clientConnectMsgVec.erase(iter);

        unregisterSocketFd(clientSocket);
        return true;
    }

    printf("has not exist\n");
    return false;

}
void LinkMgr::setWindow(void* win){
    m_window = win;
}
void LinkMgr::getClientSocketFd(int clientFd[],int& len){
    // add active connection to fd set
    len = 0;
    std::vector<int>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        cout<<"add fd ="<<*iter<<endl;
        //FD_SET(iter->first, &fdSet);
        clientFd[len++] = *iter;
    }
}
void LinkMgr::getClientSocketFd(vector<int>* vec){
    assert(vec);
    std::vector<int>::iterator iter;
    for(iter=m_clientConnectMsgVec.begin();iter!=m_clientConnectMsgVec.end();iter++){
        cout<<"add fd ="<<*iter<<endl;
        //FD_SET(iter->first, &fdSet);
        //clientFd[len++] = iter->first;
        vec->push_back(*iter);
    }
}

bool LinkMgr::addClientSocketFd(int clientFd){
    assert(clientFd>0);
    char msgBuf[100]={0};
    //manage client FD
    if(!findClient(clientFd)){// not exsit
       m_clientConnectMsgVec.push_back(clientFd);
       sprintf(msgBuf,"accept client =%d success",clientFd);
       ((MainWindow*)m_window)->appendMsg(msgBuf);
       DataDev::getInstance()->addFd(clientFd);
    }else{
        cout<<"this client="<<clientFd<<"has exist"<<endl;
        return true;
    }
    cout<<"accept socket success socket="<<clientFd<<endl;
     return true;
}
void LinkMgr::recvLinkMsg(CONNECT_MSG_TYPE type,int clientFd,int error){
    char msgBuf[100]={0};
    switch(type){
        case Connect_Close:
            assert(clientFd>0);
            removeClientSocket(clientFd);
            close(clientFd);
            sprintf(msgBuf,"connect close,clientfd=%d",clientFd);
            break;
        case Connect_Failure:
            sprintf(msgBuf,"connect failure,error=%d",error);
            break;
        case Connect_Success:
            assert(clientFd>0);
            assert(addClientSocketFd(clientFd));
            sprintf(msgBuf,"connect success,clientfd=%d",clientFd);
            break;
        case Connect_Error:
            sprintf(msgBuf,"connect error");
            break;
        case Connect_Timeout:
            sprintf(msgBuf,"connect timeout");
            break;
        default:
            sprintf(msgBuf,"connect sernior error");
            break;
    }
    ((MainWindow*)m_window)->appendMsg(msgBuf);
}








