#include "nibpmgr.h"
#include "mgrdev.h"
#include "nibpwindow.h"
#include "../common/datadev.h"
#include "../include/define.h"
#define REFRESH_TIME 30*1000 //ms
NibpMgr::NibpMgr()
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));
    MgrDev* dev = MgrDev::getInstance();
    dev->registerObject(this);
    gettimeofday(&m_tStartTimer,NULL);

    m_network = new Network();
    assert(m_network);
    assert(openFile("datafile/nibpdata.txt"));
}
NibpMgr::~NibpMgr()
{
    MgrDev::getInstance()->unregisterObject(this);

    if(m_network){
        delete m_network;
        m_network = NULL;
    }
    assert(closeFile());

}
void NibpMgr::sendData(const BYTE* buf,int len){
    //cout<<"nibpmgr  senddata"<<endl;
    if(m_network->getConnectState())
        DataDev::getInstance()->sendData(m_network->getSockFd(),Data_Msg,NIBP_CLIENT,PC_Simulator_Link,buf,len);
}

void NibpMgr::onTimer(){

    int readnum = read();

    int time = test(readnum);
    if(time!=0){ // have not start test
        printf("NibpMgr::onTimer   interval=%dms    times=%d\n",time,m_testMsg.times);
        display();
    }
}

void NibpMgr::display(){

    if(m_testMsg.usedtimeSum >= REFRESH_TIME){//auto display to ui
         ((NibpWindow*)m_Ui)->displayStatisicsResult();
         clearTestData();
     }
    if(isShowData())
        ((NibpWindow*)m_Ui)->showData(m_readBuf);

}
int NibpMgr::data_Arrived(int fd){
    BYTE buf[1024];
    memset(buf,0,sizeof(buf));
    int len = recv(fd,buf,sizeof(buf),0);
    if(len<0){
        ((NibpWindow*)m_Ui)->showData("recv failure");
    }else if(len == 0){
        ((NibpWindow*)m_Ui)->showData("this fd has close");
    }else{
        string strBuf="recv success : ";
        char tmp[10]={0};
        for(int i=0;i<len;i++){
            sprintf(tmp,"%02x ",buf[i]);
            strBuf += tmp;
        }

        ((NibpWindow*)m_Ui)->showData(strBuf.c_str());
    }

    return 0;
}
