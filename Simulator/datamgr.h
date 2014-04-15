#ifndef DATAMGR_H
#define DATAMGR_H
#include "nibpmgr.h"
#include "spo2mgr.h"
#include <vector>
#include "../include/define.h"
using namespace std;
class DataMgr
{
public:
    DataMgr(NibpMgr* pNibpMgr,Spo2Mgr* pSpo2Mgr);
    virtual ~DataMgr();


    void recvLinkData(const Msg_* msg);
    void handleCmdMsg(const CmdMsg_* cmdMsg);
private:
     NibpMgr* m_pNibpMgr;
     Spo2Mgr* m_pSpo2Mgr;
};

#endif // DATAMGR_H
