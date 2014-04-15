#include "datadev.h"
#include "mainwindow.h"
DataDev* DataDev::m_instance = new DataDev();
DataDev::DataDev(QObject *parent) :
        QThread(parent)
{
    m_initServerOk = m_serverNetwork.init();
    m_maxClientFd = m_serverNetwork.getServerSocketFd();
    m_pDataMgr = NULL;
    m_pLinkMgr = NULL;

    m_pSendDataJob = GetJobNest();
    assert(m_pSendDataJob);
    p_pSendStateMsgJob = GetJobNest();
    assert(p_pSendStateMsgJob);
}
DataDev::~DataDev(){

}

DataDev* DataDev::getInstance(){
    return m_instance;
}
void DataDev::run(){
    //cout<<"start run ........\n";
    ((MainWindow*)m_pLinkMgr->m_window)->appendMsg("start run ........");
//    while(1){
//        cout<<"hhhhhhhhhhhh"<<endl;
//        sleep(2);
//    }
    recvData();
}
void DataDev::recvData(){
    if(!m_initServerOk){
        cout<<"please init server first   thread run failure"<<endl;
        return;
    }
    fd_set fdSet;
    int clientFd=-1;
    int ret = -1;
    struct timeval tv;
    Msg_  recvMsg;
    int maxFd = -1;

    char tmpbuf[100]={0};
    while(1){
        // initialize file descriptor set
        FD_ZERO(&fdSet);
        FD_SET(m_serverNetwork.getServerSocketFd(), &fdSet);
        maxFd = m_serverNetwork.getServerSocketFd();
        // timeout setting
       tv.tv_sec = 3;
       tv.tv_usec = 0;

       m_tmpVec.clear();
        // add active connection to fd set
       m_pLinkMgr->getClientSocketFd(&m_tmpVec);
       for(int i=0;i<m_tmpVec.size();i++){
           cout<<"add fd="<<m_tmpVec[i]<<endl;
           FD_SET(m_tmpVec[i], &fdSet);
           if(maxFd<m_tmpVec[i]){
               maxFd = m_tmpVec[i];
           }
       }
//((MainWindow*)m_pLinkMgr->m_window)->appendMsg("select start ........");
        ret = select(maxFd + 1, &fdSet, NULL, NULL, &tv);
        //cout<<"select succuss  ret="<<ret<<endl;
        //((MainWindow*)m_pLinkMgr->m_window)->appendMsg("select succuss ........");
        if (ret < 0) {
            m_pLinkMgr->recvLinkMsg(Connect_Error,-1);
            sleep(1);
            continue;
        } else if (ret == 0) {
            //m_pLinkMgr->recvLinkMsg(Connect_Timeout,-1);
            continue;
        }

        // check every active client fd in the set
        for(int i=0;i<m_tmpVec.size();i++){
            if (FD_ISSET(m_tmpVec[i], &fdSet)) {
                cout<<"m_tmpVec[i]="<<m_tmpVec[i]<<endl;
                memset(&recvMsg,0,sizeof(recvMsg));
                ret = m_serverNetwork.recvData(m_tmpVec[i],&recvMsg);
                if (ret <= 0) {        // client close
                    m_pLinkMgr->recvLinkMsg(Connect_Close,m_tmpVec[i]);
                    FD_CLR(m_tmpVec[i], &fdSet);
                } else {        // receive data
                    //recvBuf[ret]='\0';
                    //((MainWindow*)m_window)->appendMsg(recvBuf);
                    //m_pDataMgr->Rec
                       //memset(&recvBuf[ret], '\0', 1);
                    cout<<"server   success rec data from client     fd="<<m_tmpVec[i]<<endl;
                    sprintf(tmpbuf,"server success recv data fd=%d",m_tmpVec[i]);
                    ((MainWindow*)m_pLinkMgr->m_window)->appendMsg(tmpbuf);

                    BYTE buf[4];
                    for(int i=0;i<4;i++){
                        buf[i]=i+10;
                    }
                    Msg_ msg;
                    msg.type = Data_Msg;
                    msg.dataMsg.type = NIBP_CLIENT;
                    memcpy(msg.dataMsg.buf,buf,4);
                    msg.dataMsg.buf_len = 4;
                    msg.dataMsg.comeForm = PC_Simulator_Link;

                    cout<<"nibpmgr  senddata"<<endl;
                    //DataDev::getInstance()->sendData(m_tmpVec[i],&msg);
                   // m_pDataMgr->recvData(&recvMsg);
                }
            }
        }


        //check serversocket is connected by other client
        if (FD_ISSET(m_serverNetwork.getServerSocketFd(), &fdSet)) {
            cout<<"start listen"<<endl;
            clientFd = m_serverNetwork.waitAccept();
            if(-1 == clientFd){
                //cout<<"clientFd=-1 accept failure errno="<<errno<<endl;
                m_pLinkMgr->recvLinkMsg(Connect_Close,clientFd,errno);
                if(EAGAIN == errno){

                }
                continue;
            }
            sprintf(tmpbuf,"connect success socketfd=%d",clientFd);
            ((MainWindow*)m_pLinkMgr->m_window)->appendMsg(tmpbuf);
            m_pLinkMgr->recvLinkMsg(Connect_Success,clientFd);
       }
    }
}

void DataDev::sendData(int fd,const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=m_pSendDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_MSG* pci=(INFO_MSG*)pkg->Alloc(sizeof(INFO_MSG));
    assert(pci);
    pci->msg = new Msg_();
    assert(pci->msg);
    pci->fd = fd;
    pci->pThis = this;
    memcpy(pci->msg,&msg,sizeof(Msg_));


    pkg->SetExecFunction(sendMsgData_);
    pkg->SetExecParam(pci);
    pkg->SetID(7);//different thread have different source. as to this ID ,can delete the soucre.

    m_pSendDataJob->SubmitJobPkg(pkg);
}
void DataDev::sendData(int fd,const char* buf,int len){
    //驱动任务巢
    CJobPkg* pkg=m_pSendDataJob->GetJobPkg(0);
    assert(pkg);


    INFO_DATA* pci=(INFO_DATA*)pkg->Alloc(sizeof(INFO_DATA));
    assert(pci);
    pci->buf = new char[len+1];
    pci->fd = fd;
    pci->len = len;
    pci->pThis = this;
    //memcpy(pci->buf,buf,sizeof(char)*len);
    strcpy(pci->buf,buf);



    pkg->SetExecFunction(sendData_);
    pkg->SetExecParam(pci);
    pkg->SetID(7);//different thread have different source. as to this ID ,can delete the soucre.

    m_pSendDataJob->SubmitJobPkg(pkg);
}
void DataDev::sendStateMsg(int fd,const Msg_* msg){
    //驱动任务巢
    CJobPkg* pkg=p_pSendStateMsgJob->GetJobPkg(0);
    assert(pkg);

    INFO_MSG* pci=(INFO_MSG*)pkg->Alloc(sizeof(INFO_MSG));
    assert(pci);
    pci->msg = new Msg_();
    assert(pci->msg);
    pci->fd = fd;
    pci->pThis = this;
    memcpy(pci->msg,&msg,sizeof(Msg_));

    pkg->SetExecFunction(sendStateMsg_);
    pkg->SetExecParam(pci);
    pkg->SetID(8);//different thread have different source. as to this ID ,can delete the soucre.

    p_pSendStateMsgJob->SubmitJobPkg(pkg);
}



void DataDev::sendData_(void* pv){
    INFO_DATA* dataMsg = (INFO_DATA*)pv;
    assert(dataMsg);

    dataMsg->pThis->m_sendMutex.lock();
    int size = dataMsg->pThis->m_serverNetwork.sendData(dataMsg->fd,dataMsg->buf,dataMsg->len);
    if(size<=0){
        printf("senddata_  send data error\n");
    }
    dataMsg->pThis->m_sendMutex.unlock();
}
void DataDev::sendMsgData_(void* pv){
    INFO_MSG* dataMsg = (INFO_MSG*)pv;
    assert(dataMsg);

    dataMsg->pThis->m_sendMutex.lock();
    int size = dataMsg->pThis->m_serverNetwork.sendData(dataMsg->fd,dataMsg->msg);
    if(size<=0){
        printf("sendMsgData  send data error\n");
    }
    dataMsg->pThis->m_sendMutex.unlock();

}

void DataDev::sendStateMsg_(void* pv){
    return sendMsgData_(pv);
}
