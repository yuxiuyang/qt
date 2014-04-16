#include "linkmgr.h"
#include <errno.h>
#include "mainwindow.h"
LinkMgr::LinkMgr(){
    m_window = NULL;
    m_initServerOk = m_serverNetwork.init();

    //start listen server
    DataDev::getInstance()->addFd(getServerFd());
}
LinkMgr::~LinkMgr(){
    std::map <int, Link*>::iterator iter;
    for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
        if(iter->second){
            delete iter->second;
            iter->second = NULL;
        }
    }
    m_clientConnectMsgMap.clear();
    m_registerClientSocketFdVec.clear();

}
int LinkMgr::getServerFd(){
    return m_serverNetwork.getServerSocketFd();
}
void LinkMgr::waitAcceptConnect(){
    int clientFd = m_serverNetwork.waitAccept();
    if(-1 == clientFd){
        cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
        if(EAGAIN == errno){

        }
        return;
    }

    assert(addClientSocketFd(clientFd));
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

bool LinkMgr::removeClientSocket(int clientSocket){
    std::map <int, Link*>::iterator iter;
    iter = m_clientConnectMsgMap.find(clientSocket);//search clientFd

    if(iter != m_clientConnectMsgMap.end()){
        if(iter->second){
            delete iter->second;
            iter->second = NULL;
        }
        DataDev::getInstance()->removeFd(clientSocket);
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
void LinkMgr::getClientSocketFd(int clientFd[],int& len){
    // add active connection to fd set
    len = 0;
    std::map <int, Link*>::iterator iter;
    for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
        cout<<"add fd ="<<iter->first<<endl;
        //FD_SET(iter->first, &fdSet);
        clientFd[len++] = iter->first;
    }
}
void LinkMgr::getClientSocketFd(vector<int>* vec){
    assert(vec);
    std::map <int, Link*>::iterator iter;
    for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
        cout<<"add fd ="<<iter->first<<endl;
        //FD_SET(iter->first, &fdSet);
        //clientFd[len++] = iter->first;
        vec->push_back(iter->first);
    }
}

bool LinkMgr::addClientSocketFd(int clientFd){
    assert(clientFd>0);
    //char msgBuf[100]={0};
    //manage client FD
    if(!findClient(clientFd)){// not exsit
        std::pair< std::map< int, Link* >::iterator, bool> ct;
        ct = m_clientConnectMsgMap.insert( std::pair <int, Link*> ( clientFd,  NULL) );
        if( ct.second ){
            printf("\n m_Event_Name_Map insert Data Success....m,size=%d,this=%lu\n",m_clientConnectMsgMap.size(),this);
            //sprintf(msgBuf,"accept client =%d success",clientFd);
            //((MainWindow*)m_window)->appendMsg(msgBuf);
            DataDev::getInstance()->addFd(clientFd);
            return true;
        }else{
             printf("\n m_Event_Name_Map insert Data fail....\n");
             return false;
        }
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
            if(addClientSocketFd(clientFd)){

            }
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
int LinkMgr::findIdentifyForwardFd(LinkSource_ source,ClientType_ type){//find Forwarded object
    LinkSource_ tmp = Monitor_UI_Link;
    if(source == PC_Simulator_Link){//come from pc simulator,so should find a fd from monitor moudle
        tmp = Monitor_UI_Link;
        
    }else if(source == Monitor_UI_Link){
        tmp = PC_Simulator_Link;
    }
    std::map <int, Link*>::iterator iter;
    for(iter=m_clientConnectMsgMap.begin();iter!=m_clientConnectMsgMap.end();iter++){
        if(iter->second->comeForm == tmp && iter->second->type == type){
            if(iter->first != iter->second->fd){
                cout<<"may be error happend,,,,,iter->first="<<iter->first<<"iter->second->fd="<<iter->second->fd<<endl;
                return -1;
            }
            return iter->first;
        }
    }
    return -1;
}

void LinkMgr::recvLinkMsg(const Link* linkMsg){
    std::map <int, Link*>::iterator iter;
    iter = m_clientConnectMsgMap.find(linkMsg->fd);//search clientFd

    if(iter == m_clientConnectMsgMap.end()){
        cout<<"not possible,may a error"<<endl;
        return;
    }

    if(m_clientConnectMsgMap[linkMsg->fd]){//delete old link msg
        delete m_clientConnectMsgMap[linkMsg->fd];
        m_clientConnectMsgMap[linkMsg->fd] = NULL;
    }

    //add new link msg
    Link* ln = new Link();
    ln->fd = linkMsg->fd;
    ln->comeForm = linkMsg->comeForm;
    ln->type = linkMsg->type;

    m_clientConnectMsgMap[linkMsg->fd] = ln;
}






