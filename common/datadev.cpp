#include "datadev.h"

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


DataDev* DataDev::m_instance = new DataDev();
DataDev::DataDev(QObject *parent) :
        QThread(parent)
{
    m_pDataJob = GetJobNest();
    assert(m_pDataJob);

    m_pthreadState = THREAD_STOP;

    CallBack_ = NULL;
}
DataDev::~DataDev(){
    m_fdVec.clear();
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
    int maxFd = -1;
    while(THREAD_RUNNING == m_pthreadState){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        // timeout setting
       tv.tv_sec = 10;
       tv.tv_usec = 0;

        // add active connection to fd set
       for(int i=0;i<m_fdVec.size();i++){
           FD_SET(m_fdVec[i], &fdSet);
           if(maxFd<m_fdVec[i]){
               maxFd = m_fdVec[i];
           }
           //cout<<"m_fdVec[i]="<<m_fdVec[i]<<"   maxFd="<<maxFd<<endl;
       }

        ret = select(maxFd + 1, &fdSet, NULL, NULL, &tv);
        //cout<<"ret="<<ret<<endl;
        if (ret < 0) {
            sleep(1);
            continue;
        } else if (ret == 0) {
            //cout<<"time out"<<endl;
            continue;
        }

        // check every active client fd in the set
        for(int i=0;i<m_fdVec.size();i++){
            if (FD_ISSET(m_fdVec[i], &fdSet)) {
                //cout<<"select success m_fdVec[i]="<<m_fdVec[i]<<endl;
                if(CallBack_)
                  CallBack_(m_fdVec[i]);
                else{
                    cout<<"please init callback first"<<endl;
                }
            }
        }
    }
}

void DataDev::sendData(int fd,const BYTE* buf,int len){
    //驱动任务巢
    CJobPkg* pkg=m_pDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_DATA* pci=(INFO_DATA*)pkg->Alloc(sizeof(INFO_DATA));
    assert(pci);
    pci->buf = new char[len+1];
    pci->fd = fd;
    pci->len = len;
    pci->pThis = this;
    memcpy(pci->buf,buf,sizeof(BYTE)*len);
    //strcpy(pci->buf,buf);



    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(1);//different thread have different source. as to this ID ,can delete the soucre.

    m_pDataJob->SubmitJobPkg(pkg);
}

void DataDev::sendData_(void* pv){
    INFO_DATA* dataMsg = (INFO_DATA*)pv;
    assert(dataMsg);

    dataMsg->pThis->m_sendMutex.lock();


    int size = send(dataMsg->fd,dataMsg->buf,dataMsg->len,0);
    if(size != dataMsg->len){
         printf("send error errno=%d\n",errno);
    }

    dataMsg->pThis->m_sendMutex.unlock();
}


bool DataDev::addFd(int fd){
    m_socketFdMutex.lock();
    if(findFd(fd)){
        cout<<"addClientFd has exist fd="<<fd<<endl;
        m_socketFdMutex.unlock();
        return true;
    }

    m_fdVec.push_back(fd);
    if(m_pthreadState!=THREAD_RUNNING){
        m_pthreadState = THREAD_RUNNING;
        start();
    }
    m_socketFdMutex.unlock();
}

bool DataDev::removeFd(int fd){
    m_socketFdMutex.lock();
    vector<int>::iterator iter=find(m_fdVec.begin(),m_fdVec.end(),fd);
    if(iter == m_fdVec.end()){
        cout<<"removeClientFd  not find sockFd="<<fd<<endl;
        m_socketFdMutex.unlock();
        return true;
    }
    if(m_fdVec.size() <= 1){//no cliend fd needed to listen
        m_pthreadState = THREAD_STOP;
        //stop();
    }
    m_fdVec.erase(iter);
    m_socketFdMutex.unlock();
    return true;
}

bool DataDev::findFd(int fd){
    vector<int>::iterator iter=find(m_fdVec.begin(),m_fdVec.end(),fd);
    if(iter == m_fdVec.end()){
        //cout<<"findClientFd  not find sockFd="<<fd<<endl;
        return false;
    }
    return true;
}
