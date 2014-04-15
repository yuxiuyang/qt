#include "datamgr.h"

DataMgr::DataMgr(NibpMgr* pNibpMgr,Spo2Mgr* pSpo2Mgr)
{
    m_pNibpMgr = pNibpMgr;
    m_pSpo2Mgr = pSpo2Mgr;
}
DataMgr::~DataMgr(){
}


void DataMgr::recvLinkData(const Msg_* msg){
    switch(msg->type){
    case Cmd_Msg:
        handleCmdMsg(&msg->cmdMsg);
        break;
    default:
        break;
    }
}
void DataMgr::handleCmdMsg(const CmdMsg_* cmdMsg){
    switch(cmdMsg->moduleType){
    case SPO2_CLIENT:
        break;
    case NIBP_CLIENT:
        break;
    default:
        break;
    }

}
