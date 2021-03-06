#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_pTestTimer = new QTimer(this);
    ui->setupUi(this);
    connect(ui->pStart_btn, SIGNAL(clicked()), this, SLOT(start_click()));
    connect(ui->pStop_btn, SIGNAL(clicked()), this, SLOT(stop_click()));
    connect(ui->pClearCon_btn, SIGNAL(clicked()), this, SLOT(clearConnectMsg_click()));
    connect(ui->pClearDisplay_btn, SIGNAL(clicked()), this, SLOT(clearDisplayMsg_click()));
    connect(ui->pExit_btn,SIGNAL(clicked()),this,SLOT(exit_click()));
    connect( m_pTestTimer, SIGNAL(timeout()), this, SLOT(sendTimer()) );

    connect(ui->pNibp_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pSpo2_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));
    connect(ui->pEcg_rb, SIGNAL(clicked(bool)), this, SLOT(radioChange()));

    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);



    m_pDataMgr = new DataMgr();
    m_pDataMgr->setWindow((void*)this);
    m_pLinkMgr = new LinkMgr();
    m_pLinkMgr->setWindow(this);
    m_pLinkMgr->m_pDataMgr = m_pDataMgr;






    m_dataType = NIBP_CLIENT;
    ui->pNibp_rb->setChecked(true);

    m_pTestTimer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::radioChange(){
    if(ui->pNibp_rb==sender()){
        m_dataType = NIBP_CLIENT;
    }else if(ui->pSpo2_rb==sender()){
        m_dataType = SPO2_CLIENT;
    }else if(ui->pEcg_rb==sender()){
        m_dataType = ECG_CLIENT;
    }
}

void MainWindow::start_click(){
    ui->pStart_label->setText("server running");
    ui->pStart_btn->setEnabled(false);
    ui->pStop_btn->setEnabled(true);

    DataDev::getInstance()->start();
//    ui->pStart_btn->setEnabled(true);
//    ui->pStop_btn->setEnabled(false);
//    ui->pStart_label->setText("server stop");
}

void MainWindow::stop_click(){
    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);
    ui->pStart_label->setText("server stop");
    DataDev::getInstance()->stop();
}

void MainWindow::clearConnectMsg_click(){
    ui->pConnectMsg_txt->clear();
}

void MainWindow::clearDisplayMsg_click(){
    ui->pDisplay_txt->clear();
}
void MainWindow::appendMsg(const char* msg){
    m_pMutex.lock();
//    QTextCursor cursor =  ui->pDisplay_txt->textCursor();
//    cursor.movePosition(QTextCursor::End);
//    ui->pDisplay_txt->setTextCursor(cursor);
//    ui->pConnectMsg_txt->append(msg);
    m_queMsgLine.push(msg);
    m_pMutex.unlock();
}
void MainWindow::exit_click(){
    close();
}
void MainWindow::appendData(const char* msg){
    m_pMutex.lock();
    m_queDataLine.push(msg);
    m_pMutex.unlock();
}
void MainWindow::appendData(const BYTE* msg,const int len){
    m_pMutex.lock();
    string strBuf="";
    char tmp[10]={0};
    for(int i=0;i<len;i++){
        sprintf(tmp,"%02x ",msg[i]);
        strBuf += tmp;
    }
    m_queDataLine.push(strBuf.c_str());
    m_pMutex.unlock();
}

void MainWindow::sendTimer(){
    //cout<<"helllooo"<<endl;
    while(!m_queDataLine.empty()){
         QTextCursor cursor =  ui->pDisplay_txt->textCursor();
         cursor.movePosition(QTextCursor::End);
         ui->pDisplay_txt->setTextCursor(cursor);
         ui->pDisplay_txt->insertPlainText(m_queDataLine.front().c_str());
         m_pMutex.lock();
         m_queDataLine.pop();
         m_pMutex.unlock();
    }

    while(!m_queMsgLine.empty()){
         QTextCursor cursor =  ui->pConnectMsg_txt->textCursor();
         cursor.movePosition(QTextCursor::End);
         ui->pConnectMsg_txt->setTextCursor(cursor);
         ui->pConnectMsg_txt->insertPlainText(m_queMsgLine.front().c_str());
         m_pMutex.lock();
         m_queMsgLine.pop();
         m_pMutex.unlock();
    }
}





