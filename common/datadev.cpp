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

    //CallBack_ = NULL;
    printf("this = %lu\n",this);
}
DataDev::~DataDev(){
    removeAll();
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
       for(int i=0;i<m_objectFdVec.size();i++){
           FD_SET(m_objectFdVec[i]->fd, &fdSet);
           if(maxFd<m_objectFdVec[i]->fd){
               maxFd = m_objectFdVec[i]->fd;
           }
           //cout<<"m_objectFdVec[i]="<<m_objectFdVec[i]<<"   maxFd="<<maxFd<<endl;
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
        for(int i=0;i<m_objectFdVec.size();i++){
            if (FD_ISSET(m_objectFdVec[i]->fd, &fdSet)) {
                //cout<<"select success m_objectFdVec[i]="<<m_objectFdVec[i]<<endl;
                assert(m_objectFdVec[i]->object);
                m_objectFdVec[i]->object->recvData(m_objectFdVec[i]->fd);
            }
        }
    }
}

void DataDev::sendData(int fd,const BYTE* buf,int len){
    m_sendMutex.lock();

    //驱动任务巢
    CJobPkg* pkg=m_pDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_DATA* pci=(INFO_DATA*)pkg->Alloc(sizeof(INFO_DATA));
    assert(pci);
    pci->buf = new BYTE[len];
    pci->fd = fd;
    pci->len = len;
    pci->pThis = this;
    memcpy(pci->buf,buf,sizeof(BYTE)*len);


    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(1);//different thread have different source. as to this ID ,can delete the soucre.

    m_pDataJob->SubmitJobPkg(pkg);

    m_sendMutex.unlock();
}

BYTE tmpBuf[100];
void DataDev::sendData(int socketFd,MsgType_ msgType,ClientType_ clientType,DataSource_ dataSource,const BYTE* buf,const int len){
    m_sendMutex.lock();
    tmpBuf[0] = 0x99;//start
    tmpBuf[1] = len+7;//
    tmpBuf[2] = msgType;
    tmpBuf[3] = clientType;
    tmpBuf[4] = dataSource;

    BYTE calSum = 0x00;
    for(int i=0;i<len;i++){
        tmpBuf[5+i] = buf[i];
        calSum += buf[i];
    }
    tmpBuf[5+len] = tmpBuf[1] + tmpBuf[2] + tmpBuf[3] +tmpBuf[4] + calSum;

    tmpBuf[5+len+1] = 0xdd;//end

     m_sendMutex.unlock();

     sendData(socketFd,tmpBuf,7+len);
}
bool DataDev::checkData(const BYTE* buf,const int len,const BYTE value){
    BYTE sum=0x00;
    for(int i=0;i<len;i++){
        sum += buf[i];
    }

    return sum==value?true:false;
}

void DataDev::sendData_(void* pv){
    INFO_DATA* dataMsg = (INFO_DATA*)pv;
    assert(dataMsg);

    int size = send(dataMsg->fd,dataMsg->buf,dataMsg->len,0);
    if(size != dataMsg->len){
         printf("send error errno=%d,size=%d\n",errno,size);
    }
}


bool DataDev::addFd(RecvObject* object,int fd){
    m_socketFdMutex.lock();
    if(findFd(fd)){
        cout<<"addClientFd has exist fd="<<fd<<endl;
        m_socketFdMutex.unlock();
        return true;
    }

    RECVOBJECT_FD *p = new RECVOBJECT_FD;
    p->object = object;
    p->fd = fd;

    m_objectFdVec.push_back(p);
    if(m_pthreadState!=THREAD_RUNNING){
        m_pthreadState = THREAD_RUNNING;
        start();
    }
    m_socketFdMutex.unlock();
}

bool DataDev::removeFd(int fd){
    m_socketFdMutex.lock();

    for(vector<RECVOBJECT_FD*>::iterator iter=m_objectFdVec.begin();iter!=m_objectFdVec.end();iter++){
        if((*iter)->fd == fd){
            delete *iter;
            m_objectFdVec.erase(iter);
        }
    }
    if(m_objectFdVec.empty()){//stop thread
        m_pthreadState = THREAD_STOP;
    }
    m_socketFdMutex.unlock();
    return true;
}
bool DataDev::removeAll(RecvObject* object){//when object is null,and delete all.
    m_socketFdMutex.lock();

    for(vector<RECVOBJECT_FD*>::iterator iter=m_objectFdVec.begin();iter!=m_objectFdVec.end();){
        if(object){
            if(object == (*iter)->object){
                delete *iter;
                m_objectFdVec.erase(iter);
            }
        }else{
            delete *iter;
            m_objectFdVec.erase(iter);
        }
    }

    m_socketFdMutex.unlock();
    return true;
}
RecvObject* DataDev::findFd(int fd){
    for(int i=0;i<m_objectFdVec.size();i++){
        if(fd == m_objectFdVec[i]->fd){
            return m_objectFdVec[i]->object;
        }
    }
    return NULL;
}
