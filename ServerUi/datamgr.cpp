#include "datamgr.h"
#include "../common/datadev.h"
#include "mainwindow.h"
#include <string>
using namespace std;

DataMgr::DataMgr()
{
    //DataDev::getInstance()->setCallback(recvData);
    memset(&m_dataBuf,0,sizeof(m_dataBuf));
    m_curPos = 0;
}
DataMgr::~DataMgr()
{
}

void DataMgr::handle(const BYTE* buf,int len){
    addBuf(buf,len);
    open_block();
}
int DataMgr::open_block(){
    int ix=0;
    while(ix<m_curPos&&m_dataBuf[ix]!=0x99){//找到 99 开头的包。找不到，则丢掉之前数据
        ix++;
    }
    if(ix!=0){//丢掉之前数据
        memmove(m_dataBuf,m_dataBuf+ix,m_curPos-ix);//这里需要用 m_curPos
        m_curPos=m_curPos-ix;
         //重新初始化
        ix = 0;
     }

     //0x99后的 第二位  即数据包长度
     if(m_curPos<2){
         return 0;//数据长度不够，下次再来解析
     }
     int len = m_dataBuf[1];
     if(m_curPos<len){//未达到完整包长度
          return 0;//数据长度不够，下次再来解析
     }
     //printf("len=%02x-%d\n",len,len);
     if(m_dataBuf[len-1]!=0xdd){//这个包有问题，应丢掉
          // throw a pag
          printf("miss a page\n");
          memcpy(m_dataBuf,m_dataBuf+len,m_curPos-len);//这里需要用 m_curPos
          m_curPos -= len;
          return 0;
      }

      //收到了一个完整的包，校验 
     if(DataDev::getInstance()->checkData(m_dataBuf+1,len-3,m_dataBuf[len-2])){//check ok
         anal_pag(m_dataBuf,len);
     }

     //analyse finished, delete this page
     memcpy(m_dataBuf,m_dataBuf+len,m_curPos-len);
     m_curPos=m_curPos-len;

}

void DataMgr::addBuf(const BYTE* buf,int len){
    if(m_curPos+len<=MAX_DATA_BUF){
          memmove(m_dataBuf+m_curPos,buf,len);
          m_curPos+=len;
    }
    else{
        if(MAX_DATA_BUF-m_curPos>0){
             memmove(m_dataBuf+m_curPos,buf,MAX_DATA_BUF-m_curPos);
             m_curPos=MAX_DATA_BUF;
        }
    }
}
bool DataMgr::anal_pag(const BYTE* buf,const int len){
    string strBuf="";
    char tmp[10]={0};
    for(int i=0;i<len;i++){
        sprintf(tmp,"%02x ",buf[i]);
        strBuf += tmp;
    }
    ((MainWindow*)m_pWindow)->appendData(strBuf.c_str());
}

void DataMgr::setWindow(void* ww){
    m_pWindow = ww;
}









