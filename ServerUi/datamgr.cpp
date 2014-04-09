#include "datamgr.h"
#include "datadev.h"
DataMgr::DataMgr()
{
    m_pSendDataJob = GetJobNest();
    assert(m_pSendDataJob);
    p_pSendStateMsgJob = GetJobNest();
    assert(p_pSendStateMsgJob);
}
DataMgr::~DataMgr()
{
    if(m_pSendDataJob){
        delete m_pSendDataJob;
        m_pSendDataJob = NULL;
    }
    if(p_pSendStateMsgJob){
        delete p_pSendStateMsgJob;
        p_pSendStateMsgJob = NULL;
    }
}
void DataMgr::sendData(int fd,const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=m_pSendDataJob->GetJobPkg(0);
    assert(pkg);


    SENDMSG_* pci=(SENDMSG_*)pkg->Alloc(sizeof(SENDMSG_));
    assert(pci);
    pci->fd = fd;
    memcpy(pci->msg,&msg,sizeof(Msg_));

    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(7);//different thread have different source. as to this ID ,can delete the soucre.

    m_pSendDataJob->SubmitJobPkg(pkg);
}
void DataMgr::sendStateMsg(int fd,const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=p_pSendStateMsgJob->GetJobPkg(0);
    assert(pkg);

    SENDMSG_* pci=(SENDMSG_*)pkg->Alloc(sizeof(SENDMSG_));
    assert(pci);
    pci->fd = fd;
    memcpy(pci->msg,&msg,sizeof(Msg_));

    pkg->SetExecFunction(sendStateMsg_);
    pkg->SetExecParam(pci);
    pkg->SetID(8);//different thread have different source. as to this ID ,can delete the soucre.

    p_pSendStateMsgJob->SubmitJobPkg(pkg);
}
void DataMgr::sendData_(void* pv){
    SENDMSG_* SendMsg = (SENDMSG_*)pv;
    assert(SendMsg);

    DataDev::getInstance()->sendData(SendMsg->fd,SendMsg->msg);
}
void DataMgr::sendStateMsg_(void* pv){
    return sendData_(pv);
}
void DataMgr::recvData(const Msg_* msg){
    switch(msg->type){
    case Link_Msg:
        //DataDev::getInstance()->m_pLinkMgr->recvLinkMsg();
        break;
    case Data_Msg:
        handDataMsg();
        break;
    case Cmd_Msg:
        handleCmdMsg();
        break;
    case Notify_Msg:
        handleNotifyMsg();
        break;
    default:
        break;

    }
}

void DataMgr::handDataMsg(){

}

void DataMgr::handleNotifyMsg(){

}

void DataMgr::handleCmdMsg(){

}












