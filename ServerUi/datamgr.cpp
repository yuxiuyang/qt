#include "datamgr.h"

DataMgr::DataMgr(QObject *parent) :
    QThread(parent)
{
    m_pSendJob = GetJobNest();
}
DataMgr::~DataMgr()
{
    if(m_pSendJob){
        delete m_pSendJob;
        m_pSendJob = NULL;
    }
}
void DataMgr::sentData(const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=m_pSendJob->GetJobPkg(0);
    assert(pkg);

    Msg_* pci=(Msg_*)pkg->Alloc(sizeof(Msg_));
    assert(pci);
    memcpy(pci,&msg,sizeof(Msg_));

    pkg->SetExecFunction(sendState);
    pkg->SetExecParam(pci);
    pkg->SetID(7);//different thread have different source. as to this ID ,can delete the soucre.

    m_pSendJob->SubmitJobPkg(pkg);
}

void DataMgr::sendState(void* pv){

}
void DataMgr::recvData(){

}

void DataMgr::run(){//used to recv data
    recvData();
}
