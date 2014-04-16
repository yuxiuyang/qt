#include "datamgr.h"
#include "../common/datadev.h"
#include "mainwindow.h"
#include <string>
using namespace std;
DataMgr* DataMgr::pThis = NULL;
DataMgr::DataMgr()
{
    DataDev::getInstance()->setCallback(recvData);

    m_pLinkMgr = new LinkMgr();
    assert(m_pLinkMgr);

    memset(&m_recvBuf,0,sizeof(m_recvBuf));

    pThis = this;
}
DataMgr::~DataMgr()
{
    delete m_pLinkMgr;
    m_pLinkMgr = NULL;
}


void DataMgr::recvData(int socket){
    if(socket == pThis->m_pLinkMgr->getServerFd()){//client try to connect server
        pThis->m_pLinkMgr->waitAcceptConnect();
        return;
    }

    char tmpbuf[100]={0};
    string strBuf = "";
    int len = recv(socket,&pThis->m_recvBuf,sizeof(pThis->m_recvBuf),0);
    if (len <= 0) {        // client close
          pThis->m_pLinkMgr->recvLinkMsg(Connect_Close,socket);
          DataDev::getInstance()->removeFd(socket);
          //cout<<""
          //FD_CLR(m_tmpVec[i], &fdSet);
     } else {        // receive data
           cout<<"server   success rec data from client     fd="<<socket<<endl;
           //sprintf(tmpbuf,"server success recv data fd=%d",socket);
         for(int i=0;i<len;i++){
             sprintf(tmpbuf,"%02x ",pThis->m_recvBuf[i]);
             strBuf += tmpbuf;
             printf("%02x ",pThis->m_recvBuf[i]);
         }
           ((MainWindow*)pThis->m_pLinkMgr->m_window)->appendData(strBuf.c_str());
//
//                        BYTE buf[4];
//                        for(int i=0;i<4;i++){
//                            buf[i]=i+10;
//                        }
//                        Msg_ msg;
//                        msg.type = Data_Msg;
//                        msg.dataMsg.type = NIBP_CLIENT;
//                        memcpy(msg.dataMsg.buf,buf,4);
//                        msg.dataMsg.buf_len = 4;
//                        msg.dataMsg.comeForm = PC_Simulator_Link;
//
//                        cout<<"nibpmgr  senddata"<<endl;
                        //DataDev::getInstance()->sendData(m_tmpVec[i],&msg);
                       // m_pDataMgr->recvData(&recvMsg);

           pThis->handle();
    }

    return;
}
void DataMgr::handle(){

}
void DataMgr::setWindow(void* ww){
    m_pWindow = ww;

    m_pLinkMgr->setWindow(ww);
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
        ((MainWindow*)(m_pLinkMgr->m_window))->appendData(buf);
    }
}









