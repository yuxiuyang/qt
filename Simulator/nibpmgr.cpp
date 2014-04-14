#include "nibpmgr.h"
#include "mgrdev.h"
#include "nibpwindow.h"
#define REFRESH_TIME 30*1000 //ms
NibpMgr::NibpMgr()
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
NibpMgr::~NibpMgr()
{
    MgrDev::getInstance()->unregisterObject(this);

    if(m_network){
        delete m_network;
        m_network = NULL;
    }
    assert(closeFile());
}
void NibpMgr::onTimer(){

    read();
    display();

    //send to data  to server


}
void NibpMgr::display(){
    if(!BasicMgr::test()) return; // have not start test

    if(m_testMsg.timeSum >= REFRESH_TIME){//auto display to ui
         ((NibpWindow*)m_Ui)->displayStatisicsResult();
         m_testMsg.times = 0;
         m_testMsg.timeSum = 0;
         m_testMsg.readSum = 0;
     }
    if(isShowData())
        ((NibpWindow*)m_Ui)->showData(m_readBuf);

}
