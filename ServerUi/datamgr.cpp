#include "datamgr.h"
#include "datadev.h"
#include "mainwindow.h"
DataMgr::DataMgr()
{

}
DataMgr::~DataMgr()
{

}


void DataMgr::recvData(const Msg_* msg){
    LinkSource_ comeFrom = PC_Simulator_Link;
    ClientType_ type = ECG_CLIENT;
    switch(msg->type){
    case Link_Msg:
        comeFrom = msg->linkMsg.comeForm;
        type = msg->linkMsg.type;
        DataDev::getInstance()->m_pLinkMgr->recvLinkMsg(&(msg->linkMsg));
        break;
    case Data_Msg:
        comeFrom = msg->dataMsg.comeForm;
        type = msg->dataMsg.type;
        handDataMsg(&msg->dataMsg);
        break;
    case Cmd_Msg:
        comeFrom = msg->cmdMsg.comeForm;
        type = msg->cmdMsg.moduleType;
        handleCmdMsg(&msg->cmdMsg);
        break;
    case Notify_Msg:
        comeFrom = msg->notifyMsg.comeForm;
        type = msg->notifyMsg.type;
        handleNotifyMsg(&msg->notifyMsg);
        break;
    default:
        break;

    }

    int convertFd = DataDev::getInstance()->m_pLinkMgr->findIdentifyForwardFd(comeFrom,type);
    convertDatas(convertFd,msg);

    return;
}

void DataMgr::handDataMsg(const DataMsg_* dataMsg){
//    int socketFd = DataDev::getInstance()->m_pLinkMgr->findIdentifyForwardFd(dataMsg->comeForm,dataMsg->type);
//    if(socketFd==-1){
//        printf("may disconnect  type=%d",dataMsg->type);
//        return;
//    }
//
//      //this is data msg ,and should convert to Monitor or ui
//     DataDev::getInstance()->sendData(socketFd,dataMsg->buf,dataMsg->buf_len);//convert to monitor or ui

}

void DataMgr::handleCmdMsg(const CmdMsg_* cmdMsg){
}

void DataMgr::handleNotifyMsg(const NotifyMsg_* notifyMsg){
}

void DataMgr::convertDatas(int fd,const Msg_* msg){
    assert(fd>0);
    //DataDev::getInstance()->sendData(fd,msg);//

    if(msg->type == Data_Msg){
        char buf[1000]={0};
        int i=0;
        for(;i<msg->dataMsg.buf_len;i++){
            sprintf(buf+i,"%02x ",msg->dataMsg.buf[i]);
        }
        buf[i] = '\0';
        ((MainWindow*)(DataDev::getInstance()->m_pLinkMgr->m_window))->appendMsg(SPO2_CLIENT,buf);
    }
}









