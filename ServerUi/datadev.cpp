#include "datadev.h"
DataDev* DataDev::m_instance = new DataDev();
DataDev::DataDev(QObject *parent) :
        QThread(parent)
{
    m_initServerOk = m_serverNetwork.init();
    m_maxClientFd = m_serverNetwork.getServerSocketFd();
    m_pDataMgr = NULL;
    m_pLinkMgr = NULL;
}
DataDev::~DataDev(){
    assert(m_instance);
}

DataDev* DataDev::getInstance(){
    return m_instance;
}
void DataDev::run(){
    if(!m_initServerOk){
        cout<<"please init server first   thread run failure"<<endl;
        return;
    }
    fd_set fdSet;
    int clientFd=-1;
    int ret = -1;
    struct timeval tv;
    Msg_  recvMsg;
    int maxFd = -1;
    while(1){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        FD_SET(m_serverNetwork.getServerSocketFd(), &fdSet);
        maxFd = m_serverNetwork.getServerSocketFd();
        // timeout setting
       tv.tv_sec = 3000000;
       tv.tv_usec = 0;

       m_tmpVec.clear();
        // add active connection to fd set
       m_pLinkMgr->getClientSocketFd(&m_tmpVec);
       for(int i=0;i<m_tmpVec.size();i++){
           FD_SET(m_tmpVec[i], &fdSet);
           if(maxFd<m_tmpVec[i]){
               maxFd = m_tmpVec[i];
           }
       }

        ret = select(maxFd + 1, &fdSet, NULL, NULL, &tv);
        if (ret < 0) {
            m_pLinkMgr->recvLinkMsg(Connect_Error,-1);
            sleep(1);
            continue;
        } else if (ret == 0) {
            m_pLinkMgr->recvLinkMsg(Connect_Timeout,-1);
            continue;
        }

        // check every active client fd in the set
        for(int i=0;i<m_tmpVec.size();i++){
            if (FD_ISSET(m_tmpVec[i], &fdSet)) {
                cout<<"m_tmpVec[i]="<<m_tmpVec[i]<<endl;
                memset(&recvMsg,0,sizeof(recvMsg));
                ret = m_serverNetwork.recvData(m_tmpVec[i],&recvMsg);
                if (ret <= 0) {        // client close
                    m_pLinkMgr->recvLinkMsg(Connect_Close,m_tmpVec[i]);
                    FD_CLR(m_tmpVec[i], &fdSet);
                } else {        // receive data
                    //recvBuf[ret]='\0';
                    //((MainWindow*)m_window)->appendMsg(recvBuf);
                    //m_pDataMgr->Rec
                       //memset(&recvBuf[ret], '\0', 1);
                    m_pDataMgr->recvData(&recvMsg);
                }
            }
        }


        //check serversocket is connected by other client
        if (FD_ISSET(m_serverNetwork.getServerSocketFd(), &fdSet)) {
            cout<<"start listen"<<endl;
            clientFd = m_serverNetwork.waitAccept();
            if(-1 == clientFd){
                //cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
                m_pLinkMgr->recvLinkMsg(Connect_Close,clientFd,errno);
                if(EAGAIN == errno){

                }
                continue;
            }
            m_pLinkMgr->recvLinkMsg(Connect_Success,clientFd);
       }
    }
}
int DataDev::sendData(int fd,const Msg_* msg){
    assert(fd>0);
    return m_serverNetwork.sendData(fd,msg);
}