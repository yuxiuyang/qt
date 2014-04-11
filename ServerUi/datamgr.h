#ifndef DATAMGR_H
#define DATAMGR_H
#include "../include/define.h"

class DataMgr
{
public:
    DataMgr();
    ~DataMgr();

public:
    void recvData(const Msg_* msg);

protected:

    void handDataMsg(const DataMsg_* dataMsg);
    void handleCmdMsg(const CmdMsg_* cmdMsg);
    void handleNotifyMsg(const NotifyMsg_* notifyMsg);

    void convertDatas(int fd,const Msg_* msg);




private:

};

#endif // DATAMGR_H
