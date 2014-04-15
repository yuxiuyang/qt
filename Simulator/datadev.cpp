#include "datadev.h"

#include "netdev.h"
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


DataDev* DataDev::m_instance = new DataDev();
DataDev::DataDev(DataMgr* pMgr,QObject *parent) :
        QThread(parent)
{
    m_pDataJob = GetJobNest();
    assert(m_pDataJob);


    m_pthreadState = THREAD_STOP;
    m_pDataMgr = pMgr;
}
DataDev::~DataDev(){
    m_clientFdVec.clear();
}

DataDev* DataDev::getInstance(){
    return m_instance;
}
void DataDev::run(){//device recv data
    cout<<"run start"<<endl;
    recvData();
    cout<<"run end.."<<endl;
}

void DataDev::recvData(){
    fd_set fdSet;
    int ret = -1;
    struct timeval tv;
    Msg_  recvMsg;
    int maxFd = -1;
    while(THREAD_RUNNING == m_pthreadState){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        // timeout setting
       tv.tv_sec = 3;
       tv.tv_usec = 0;

        // add active connection to fd set
       for(int i=0;i<m_clientFdVec.size();i++){
           FD_SET(m_clientFdVec[i], &fdSet);
           if(maxFd<m_clientFdVec[i]){
               maxFd = m_clientFdVec[i];
           }
           cout<<"m_clientFdVec[i]="<<m_clientFdVec[i]<<"   maxFd="<<maxFd<<endl;
       }

        ret = select(maxFd + 1, &fdSet, NULL, NULL, &tv);
        cout<<"ret="<<ret<<endl;
        if (ret < 0) {
            sleep(1);
            continue;
        } else if (ret == 0) {
            cout<<"time out"<<endl;
            continue;
        }

        // check every active client fd in the set
        for(int i=0;i<m_clientFdVec.size();i++){
            if (FD_ISSET(m_clientFdVec[i], &fdSet)) {
                memset(&recvMsg,0,sizeof(recvMsg));
                ret = recv(m_clientFdVec[i],&recvMsg,sizeof(Msg_),0);
                if (ret <= 0) {        // client close
                    printf("client close client=%d\n",m_clientFdVec[i]);
                    removeClientFd(m_clientFdVec[i]);
                    FD_CLR(m_clientFdVec[i], &fdSet);
                } else {        // receive data

                    //((MainWindow*)m_window)->appendMsg(recvBuf);
                    m_pDataMgr->recvLinkData(&recvMsg);
                }
            }
        }
    }
}

void DataDev::sendData(int fd,const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=m_pDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_MSG* pci=(INFO_MSG*)pkg->Alloc(sizeof(INFO_MSG));
    assert(pci);
    pci->msg = new Msg_();
    assert(pci->msg);
    pci->fd = fd;
    pci->pThis = this;
    memcpy(pci->msg,&msg,sizeof(Msg_));


    pkg->SetExecFunction(sendMsgData_);
    pkg->SetExecParam(pci);
    pkg->SetID(1);//different thread have different source. as to this ID ,can delete the soucre.

    m_pDataJob->SubmitJobPkg(pkg);
}
void DataDev::sendData(int fd,const char* buf,int len){
    //驱动任务巢
    CJobPkg* pkg=m_pDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_DATA* pci=(INFO_DATA*)pkg->Alloc(sizeof(INFO_DATA));
    assert(pci);
    pci->buf = new char[len+1];
    pci->fd = fd;
    pci->len = len;
    pci->pThis = this;
    //memcpy(pci->buf,buf,sizeof(char)*len);
    strcpy(pci->buf,buf);



    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(1);//different thread have different source. as to this ID ,can delete the soucre.

    m_pDataJob->SubmitJobPkg(pkg);
}

void DataDev::sendData_(void* pv){
    INFO_DATA* dataMsg = (INFO_DATA*)pv;
    assert(dataMsg);

    dataMsg->pThis->m_sendMutex.lock();
//    int size = dataMsg->pThis->m_serverNetwork.sendData(dataMsg->fd,dataMsg->buf,dataMsg->len);
//    if(size<=0){
//        printf("senddata_  send data error\n");
//    }
    dataMsg->pThis->m_sendMutex.unlock();
}
void DataDev::sendMsgData_(void* pv){
    INFO_MSG* dataMsg = (INFO_MSG*)pv;
    assert(dataMsg);

    dataMsg->pThis->m_sendMutex.lock();
//    int size = dataMsg->pThis->m_serverNetwork.sendData(dataMsg->fd,dataMsg->msg);
//    if(size<=0){
//        printf("sendMsgData  send data error\n");
//    }
    dataMsg->pThis->m_sendMutex.unlock();

}


bool DataDev::addClientFd(int fd){
    m_socketFdMutex.lock();
    if(findClientFd(fd)){
        printf("addClientFd  has exist fd=%d\n",fd);
        m_socketFdMutex.unlock();
        return true;
    }

    m_clientFdVec.push_back(fd);
    if(m_pthreadState!=THREAD_RUNNING){
        m_pthreadState = THREAD_RUNNING;
        start();
    }
    m_socketFdMutex.unlock();
}

bool DataDev::removeClientFd(int fd){
    m_socketFdMutex.lock();
    vector<int>::iterator iter=find(m_clientFdVec.begin(),m_clientFdVec.end(),fd);
    if(iter == m_clientFdVec.end()){
        cout<<"removeClientFd  not find sockFd="<<fd<<endl;
        m_socketFdMutex.unlock();
        return true;
    }
    if(m_clientFdVec.size() <= 1){//no cliend fd needed to listen
        m_pthreadState = THREAD_STOP;
        //stop();
    }
    m_clientFdVec.erase(iter);
    m_socketFdMutex.unlock();
    return true;
}

bool DataDev::findClientFd(int fd){
    vector<int>::iterator iter=find(m_clientFdVec.begin(),m_clientFdVec.end(),fd);
    if(iter == m_clientFdVec.end()){
        //cout<<"findClientFd  not find sockFd="<<fd<<endl;
        return false;
    }
    return true;
}
