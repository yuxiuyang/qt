#include "nibpwindow.h"
#include "ui_nibpwindow.h"
#include <QString>
#include <QMessageBox>
#include <iostream>
using namespace std;
NibpWindow::NibpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NibpWindow)
{
    ui->setupUi(this);
    connect(ui->pExit_btn, SIGNAL(clicked()), this, SLOT(exit_click()));
    connect(ui->pClear_btn, SIGNAL(clicked()), this, SLOT(clear_click()));
    connect(ui->pFreOk_btn, SIGNAL(clicked()), this, SLOT(freOk_click()));
    connect(ui->pFreCancel_btn, SIGNAL(clicked()), this, SLOT(freCancel_click()));
    connect(ui->pRcOk_btn, SIGNAL(clicked()), this, SLOT(rcOk_click()));
    connect(ui->pRcCancel_btn, SIGNAL(clicked()), this, SLOT(rcCancel_click()));
    connect(ui->pST_check, SIGNAL(stateChanged(int)), this, SLOT(startTestCheckStateChanged(int)));
    connect(ui->pGenerateData_check,SIGNAL(stateChanged(int)), this, SLOT(genarateNewDataCheckStateChanged(int)));
    connect(ui->pShowReadData_check,SIGNAL(stateChanged(int)),this,SLOT(showReadDataCheckStateChanged(int)));
    connect(ui->pConnect_btn, SIGNAL(clicked()), this, SLOT(connectNetwork()));
    connect(ui->pDisConnect_btn, SIGNAL(clicked()), this, SLOT(disConnectNetwork()));
    connect(ui->pSendTestData_btn, SIGNAL(clicked()), this, SLOT(sendTestData()));

    m_nibpMgr = new NibpMgr();
    assert(m_nibpMgr);
    m_nibpMgr->setWindow((void*)this);
    m_nibpMgr->setFrequency(1);
    m_nibpMgr->setReadNum(9);

    ui->pFre_edit->append(QString::number(m_nibpMgr->getFrequency()));
    ui->pTm_edit->append("1000");
    ui->pTm_edit->setReadOnly(true);
    ui->pTm_edit->setEnabled(false);

    ui->pRc_edit->append(QString::number(m_nibpMgr->getReadNum()));

    ui->pFreOk_btn->setEnabled(false);
    ui->pRcOk_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(false);
    ui->pFre_edit->setEnabled(false);

    ui->pDisConnect_btn->setEnabled(false);
}

NibpWindow::~NibpWindow()
{
    delete m_nibpMgr;
    m_nibpMgr = NULL;

    delete ui;
}

void NibpWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void NibpWindow::exit_click(){
    hide();
    if(m_object){
        m_object->setWindowTitle("Main Window");
    }
}
void NibpWindow::clear_click(){
    ui->pMsg_Txt->clear();
}
void NibpWindow::freOk_click(){
    ui->pFreOk_btn->setEnabled(false);
    ui->pFreCancel_btn->setEnabled(true);
    ui->pFre_edit->setEnabled(false);
    ui->pFreCancel_btn->setFocus();

    QString str = ui->pFre_edit->toPlainText();

    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        ui->pFre_edit->append("error");
        return;
    }
    //ui->pMsg_Txt->append(str);
    m_nibpMgr->setFrequency(val);

    ui->pTm_edit->clear();
    ui->pTm_edit->append(QString::number(m_nibpMgr->getTimeout()));


//    char buf[100]={0};
//    sprintf(buf,"3214");
//    cout<<"start buf="<<buf<<endl;
//    BYTE buf[5];
//    for(int i=0;i<5;i++){
//        buf[i] = i+1;
//    }
//    que.push(buf,5);
}

void NibpWindow::freCancel_click(){
    ui->pFreOk_btn->setEnabled(true);
    ui->pFreCancel_btn->setEnabled(false);
    ui->pFre_edit->setEnabled(true);
    ui->pFreOk_btn->setFocus();


//    BYTE data[100]={0};
//    que.getDatas(data,3);
//    //cout<<data[0]<<" "<<data[1]<<" ";
//    char buf[100]={0};
//    sprintf(buf,"%d %d %d ",data[0],data[1],data[2]);
//    ui->pMsg_Txt->insertPlainText(buf);
}

void NibpWindow::rcOk_click(){
    ui->pRcOk_btn->setEnabled(false);
    ui->pRcCancel_btn->setEnabled(true);
    ui->pRc_edit->setEnabled(false);
    ui->pRcCancel_btn->setFocus();

    QString str = ui->pFre_edit->toPlainText();
    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        ui->pFre_edit->append("error");
        return;
    }
    cout<<"val="<<val<<endl;
    m_nibpMgr->setReadNum(val);
}

void NibpWindow::rcCancel_click(){
    ui->pRcOk_btn->setEnabled(true);
    ui->pRcCancel_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(true);
    ui->pRcOk_btn->setFocus();
}
void NibpWindow::connectNetwork(){
    ui->pConnect_btn->setEnabled(false);
    ui->pConnect_btn->setText("connecting");
    if(m_nibpMgr->connect()){
        ui->pConnect_btn->setText("connect success");
        ui->pDisConnect_btn->setEnabled(true);
    }else{
        ui->pConnect_btn->setEnabled(true);
        ui->pConnect_btn->setText("connect");
        ui->pDisConnect_btn->setEnabled(false);
    }
}
void NibpWindow::disConnectNetwork(){
    ui->pConnect_btn->setText("connect");
    ui->pConnect_btn->setEnabled(true);
    ui->pDisConnect_btn->setEnabled(false);

    m_nibpMgr->disConnect();
}
void NibpWindow::sendTestData(){
    char buf[]="nibpwindow data";
    printf("send buf=%s\n",buf);
    m_nibpMgr->sendTestData(buf,sizeof(buf));
}

void NibpWindow::startTestCheckStateChanged(int state){
    if(ui->pST_check->isChecked()){
        m_nibpMgr->startTest();
        showData("");
    }else{
        m_nibpMgr->stopTest();
    }
}
void NibpWindow::genarateNewDataCheckStateChanged(int state){
    if(ui->pGenerateData_check->isChecked()){
        m_nibpMgr->generateTestFile();
        cout<<"generate new data ok"<<endl;
    }
}

void NibpWindow::showReadDataCheckStateChanged(int state){
        m_nibpMgr->setShowDataSign(ui->pShowReadData_check->isChecked());
}

void NibpWindow::displayStatisicsResult(){
    TESTMSG* msg = m_nibpMgr->getTestMsg();
    static char buf[100]={0};
    sprintf(buf,"timeSum=%ld",msg->timeSum);
    ui->pStatistics_txt->append(buf);
    sprintf(buf,"readSum=%ld",msg->readSum);
    ui->pStatistics_txt->append(buf);
    sprintf(buf,"times=%ld",msg->times);
    ui->pStatistics_txt->append(buf);
    ui->pStatistics_txt->append("------------caculator------------");

    sprintf(buf,"arg_time1=%4.1f (ms each)",(float)msg->timeSum/(float)msg->times);
    ui->pStatistics_txt->append(buf);

    sprintf(buf,"arg_time2=%4.1f (ts/s)",((float)msg->times/(float)msg->timeSum)*1000.);
    ui->pStatistics_txt->append(buf);

    sprintf(buf,"arg_read1=%4.1f (one each)",(float)msg->readSum/(float)msg->times);
    ui->pStatistics_txt->append(buf);
    sprintf(buf,"arg_read2=%4.1f (n/s)",(float)msg->readSum/(float)msg->times*1000);
    ui->pStatistics_txt->append(buf);

    /*QTextCursor cs=ui.chat_edit->textCursor();
                cs.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
                cs.movePosition(QTextCursor::NextBlock,QTextCursor::KeepAnchor, iLines);
                cs.removeSelectedText();
          qt qtextbrowser 添加字符
*/
}
void NibpWindow::showData(char* buf){
    ui->pMsg_Txt->insertPlainText(buf);
}
