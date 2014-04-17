#include "spo2mgr.h"
#include "mgrdev.h"
#include "spo2window.h"
#define REFRESH_TIME 30*1000 //ms
Spo2Mgr::Spo2Mgr()
{
    memset(&m_tStartTimer,0,sizeof(m_tStartTimer));
    MgrDev* dev = MgrDev::getInstance();
    dev->registerObject(this);
    gettimeofday(&m_tStartTimer,NULL);

    m_network = new Network();
    //m_network->init();
    assert(m_network);
    assert(openFile("datafile/spo2data.txt"));
}
Spo2Mgr::~Spo2Mgr()
{
    MgrDev::getInstance()->unregisterObject(this);

    if(m_network){
        delete m_network;
        m_network = NULL;
    }
    assert(closeFile());
}
void Spo2Mgr::onTimer(){

    read();
    display();

}
void Spo2Mgr::display(){
    if(!BasicMgr::test()) return; // have not start test

    if(m_testMsg.timeSum >= REFRESH_TIME){//auto display to ui
         ((Spo2Window*)m_Ui)->displayStatisicsResult();
         m_testMsg.times = 0;
         m_testMsg.timeSum = 0;
         m_testMsg.readSum = 0;
     }
    if(isShowData())
        ((Spo2Window*)m_Ui)->showData(m_readBuf);

}
int Spo2Mgr::recvData(int fd){
    return 0;
}
void Spo2Mgr::sendData(const BYTE* buf,int len){
    if(m_network->getConnectState())
        DataDev::getInstance()->sendData(m_network->getSockFd(),Data_Msg,SPO2_CLIENT,PC_Simulator_Link,buf,len);
}
