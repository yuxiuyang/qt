#include "mgrdev.h"

#include <assert.h>
#include<algorithm>
#include "basicmgr.h"
#include <iostream>
using namespace std;

MgrDev* MgrDev::m_instance = new MgrDev();
MgrDev::MgrDev(QObject *parent) :
    QThread(parent)
{
    m_timer = new QTimer(this);
    assert(m_timer);
}
MgrDev::~MgrDev(){
    assert(m_instance);
    stop();
    delete m_timer;
    m_timer = NULL;
}
MgrDev* MgrDev::getInstance(){
    assert(m_instance);
    return m_instance;
}

void MgrDev::run(){
//     // 使用一个线程,跑定时器
//     _TimerThread = new QThread;
//     assert(_TimerThread);
//     _WriteTimer = new QTimer;
//     assert(_WriteTimer);
//     //WriteTimer->setSingleShot(true);//just call one time
//     // 在moveToThread前先启动定时器,不然不在一个线程里,直接调用start会失败
//     _WriteTimer->start(1000);
//     _WriteTimer->moveToThread(_TimerThread);
//     // 定时器对象和this不在一个线程里面,因此这边指定了连接方式为Qt::DirectConnection,由定时器所在线程直接触发_onVoiceTimeout
//     assert(connect(_WriteTimer, SIGNAL(timeout()), this, SLOT(_onWriteTimeout()), Qt::DirectConnection));
//     // 连接定时器槽,用来停止定时器
//     //connect(this, SIGNAL(WriteTimestop()), _WriteTimer, SLOT(stop()));
//     //connect(this, SIGNAL(stop()),_WriteTimer, SLOT(stop()));
//     _TimerThread->start();

//    m_timer = new QTimer(this);//just along to main thread
//    assert(m_timer);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(_onWriteTimeout()), Qt::DirectConnection);
    m_timer->start(BASIC_TIMER_TIME);
    cout<<"start thread and timer"<<endl;
    exec();
    cout<<"end thread timer "<<endl;
}


void MgrDev::_onWriteTimeout()
{
  //获取系统当前时间
  //QTime time = QTime::currentTime();
  //设置晶体管控件QLCDNumber上显示的内容
  //lcd->display(time.toString("hh:mm:ss"));
//    char buf[100];
//    sprintf(buf,"MgrDev  threadid=%lu",pthread_self());
//    cout<<buf<<endl;

    if(m_vecObject.size()<=0) return;
    //cout<<"m_vecObject.size()="<<m_vecObject.size()<<endl;
    for(vector<void*>::iterator iter=m_vecObject.begin();iter!=m_vecObject.end();iter++){
        BasicMgr* mgr = (BasicMgr*)(*iter);
        mgr->m_iCurTime+=2;
        if(mgr->m_iCurTime >= mgr->getTimeout()){
            mgr->onTimer();
            mgr->m_iCurTime = 0;
        }
    }
}

void MgrDev::stop()
{
    assert(m_timer);
    if ( m_timer->isActive() ){
        cout<<"stop timer"<<endl;
        m_timer->stop();
        quit();//exit timer thread
        wait();
    }
}
bool MgrDev::registerObject(void* object){
    assert(object);
    if(findObject(object)){//has exist
        return false;
    }
    m_vecObject.push_back(object);
    return true;

}
bool MgrDev::unregisterObject(void* object){
    assert(object);
    vector<void*>::iterator iter = find(m_vecObject.begin(),m_vecObject.end(),object);
    if(iter==m_vecObject.end()){//has no exist
        return false;
    }

    m_vecObject.erase(iter);
}
bool MgrDev::findObject(void* object){
    assert(object);
    vector<void*>::iterator iter = find(m_vecObject.begin(),m_vecObject.end(),object);
    return iter==m_vecObject.end()?false:true;
}
