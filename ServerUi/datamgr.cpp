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

    memcpy(m_dataBuf,0,sizeof(m_dataBuf));
    m_pWirte = m_pRead = 0;
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

    char tmpbuf[200]={0};
    int len = recv(socket,&tmpbuf,sizeof(tmpbuf),0);
    if (len <= 0) {        // client close
          pThis->m_pLinkMgr->recvLinkMsg(Connect_Close,socket);
          DataDev::getInstance()->removeFd(socket);
          //cout<<""
          //FD_CLR(m_tmpVec[i], &fdSet);
     } else {        // receive data
           cout<<"server   success rec data from client     fd="<<socket<<endl;        
           //((MainWindow*)pThis->m_pLinkMgr->m_window)->appendData(strBuf.c_str());
           pThis->handle();
    }

    return;
}
void DataMgr::handle(){

}
void DataMgr::setBuf(const BYTE* buf,int len){
    if(m_pRead+len>MAX_DATA_BUF){
        memmove(m_dataBuf+m_pWrite,buf,len);
    }else{
        memmove(m_dataBuf+m_pWrite,buf,MAX_DATA_BUF-m_pWrite);

        if(m_pRead>len-(MAX_DATA_BUF-m_pWrite)){
            memmove(m_dataBuf,buf+(MAX_DATA_BUF-m_pWrite),len-(MAX_DATA_BUF-m_pWrite));
            m_pWrite = len-(MAX_DATA_BUF-m_pWrite);
        }else{
            //data too much ,miss some datas
        }
    }
}

void DataMgr::setWindow(void* ww){
    m_pWindow = ww;

    m_pLinkMgr->setWindow(ww);
}









