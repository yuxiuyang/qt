#ifndef DATAMGR_H
#define DATAMGR_H

#include <QThread>
#include "l_jn.h"
#include "../include/define.h"
struct SENDMSG_{
    int fd;
    Msg_* msg;
};

class DataMgr
{
public:
    DataMgr();
    ~DataMgr();

public:
    void sendData(int fd,const Msg_* msg);
    void sendStateMsg(int fd,const Msg_* msg);


    void recvData(const Msg_* msg);

protected:
    static void sendData_(void* pv);
    static void sendStateMsg_(void* pv);


    void handDataMsg();
    void handleNotifyMsg();
    void handleCmdMsg();



private:
    CJobNest *m_pSendDataJob;//send data task thread.
    CJobNest *p_pSendStateMsgJob;//send state msg thread
};

#endif // DATAMGR_H
