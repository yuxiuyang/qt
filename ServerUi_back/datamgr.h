#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"
#include "linkmgr.h"

#define MAX_RECIEVE_BUF 1024
class DataMgr
{
public:
    DataMgr();
    ~DataMgr();

public:
    static void recvData(int fd);
    void setWindow(void*);
protected:

    void handDataMsg(const DataMsg_* dataMsg);
    void handleCmdMsg(const CmdMsg_* cmdMsg);
    void handleNotifyMsg(const NotifyMsg_* notifyMsg);
    void handle();

    void convertDatas(int fd,const Msg_* msg);



private:
    LinkMgr* m_pLinkMgr;

    BYTE m_recvBuf[MAX_DATA_BUF];

    void* m_pWindow;
};

#endif // DATAMGR_H
