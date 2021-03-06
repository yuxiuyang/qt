#include "spo2window.h"
#include "ui_spo2window.h"
#include <QString>
#include <QMessageBox>
#include <iostream>
using namespace std;
//Queue que(10);
Spo2Window::Spo2Window(QWidget *parent) :
    //QWidget(parent),
    QDialog(parent),
    ui(new Ui::Spo2Window)
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

    m_spo2Mgr = new Spo2Mgr();
    assert(m_spo2Mgr);
    m_spo2Mgr->setWindow((void*)this);
    m_spo2Mgr->setFrequency(1);
    m_spo2Mgr->setReadNum(9);

    ui->pFre_edit->append(QString::number(m_spo2Mgr->getFrequency()));
    ui->pTm_edit->append("1000");
    ui->pTm_edit->setReadOnly(true);
    ui->pTm_edit->setEnabled(false);

    ui->pRc_edit->append(QString::number(m_spo2Mgr->getReadNum()));

    ui->pFreOk_btn->setEnabled(false);
    ui->pRcOk_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(false);
    ui->pFre_edit->setEnabled(false);

    ui->pDisConnect_btn->setEnabled(false);
}

Spo2Window::~Spo2Window()
{
    delete m_spo2Mgr;
    m_spo2Mgr = NULL;

    delete ui;
}

void Spo2Window::changeEvent(QEvent *e)
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
void Spo2Window::exit_click(){
    hide();
    if(m_object){
        m_object->setWindowTitle("Main Window");
    }
}
void Spo2Window::clear_click(){
    ui->pMsg_Txt->clear();
}
void Spo2Window::freOk_click(){
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
    m_spo2Mgr->setFrequency(val);

    ui->pTm_edit->clear();
    ui->pTm_edit->append(QString::number(m_spo2Mgr->getTimeout()));
}

void Spo2Window::freCancel_click(){
    ui->pFreOk_btn->setEnabled(true);
    ui->pFreCancel_btn->setEnabled(false);
    ui->pFre_edit->setEnabled(true);
    ui->pFreOk_btn->setFocus();

}

void Spo2Window::rcOk_click(){
    ui->pRcOk_btn->setEnabled(false);
    ui->pRcCancel_btn->setEnabled(true);
    ui->pRc_edit->setEnabled(false);
    ui->pRcCancel_btn->setFocus();

    QString str = ui->pRc_edit->toPlainText();
    bool toIntOk = false;
    int val = str.toInt(&toIntOk,10);
    if(!toIntOk){
        ui->pFre_edit->append("error");
        return;
    }
    cout<<"val="<<val<<endl;
    m_spo2Mgr->setReadNum(val);

    ui->pMsg_Txt->clear();
    ui->pStatistics_txt->clear();
}

void Spo2Window::rcCancel_click(){
    ui->pRcOk_btn->setEnabled(true);
    ui->pRcCancel_btn->setEnabled(false);
    ui->pRc_edit->setEnabled(true);
    ui->pRcOk_btn->setFocus();
}
void Spo2Window::connectNetwork(){
    ui->pConnect_btn->setEnabled(false);
    ui->pConnect_btn->setText("connecting");
    if(m_spo2Mgr->connect()){
        ui->pConnect_btn->setText("connect success");
        ui->pDisConnect_btn->setEnabled(true);
    }else{
        ui->pConnect_btn->setEnabled(true);
        ui->pConnect_btn->setText("connect");
        ui->pDisConnect_btn->setEnabled(false);
    }
}
void Spo2Window::disConnectNetwork(){
    ui->pConnect_btn->setText("connect");
    ui->pConnect_btn->setEnabled(true);
    ui->pDisConnect_btn->setEnabled(false);

    m_spo2Mgr->disConnect();
}

void Spo2Window::startTestCheckStateChanged(int state){
    if(ui->pST_check->isChecked()){
        m_spo2Mgr->startTest();
        showData("");
    }else{
        m_spo2Mgr->stopTest();
    }
}
void Spo2Window::genarateNewDataCheckStateChanged(int state){
    if(ui->pGenerateData_check->isChecked()){
        m_spo2Mgr->generateTestFile();
        cout<<"generate new data ok"<<endl;
    }
}

void Spo2Window::showReadDataCheckStateChanged(int state){
        m_spo2Mgr->setShowDataSign(ui->pShowReadData_check->isChecked());
}

void Spo2Window::displayStatisicsResult(){
    appendStatisticsMsg("------------caculator  start ------------");
    TESTMSG* msg = m_spo2Mgr->getTestMsg();
    static char buf[100]={0};
    sprintf(buf,"used time=%ld",msg->usedtimeSum);
    appendStatisticsMsg(buf);
    sprintf(buf,"readSum=%ld",msg->readSum);
    appendStatisticsMsg(buf);
    sprintf(buf,"times=%ld",msg->times);
    appendStatisticsMsg(buf);

    sprintf(buf,"arg_time1=%4.1f (ms)",(float)msg->usedtimeSum/(float)msg->times);
    appendStatisticsMsg(buf);

//    sprintf(buf,"arg_time2=%4.1f (ts/s)",((float)msg->times/(float)msg->timeSum)*1000.);
//    appendStatisticsMsg(buf);

    sprintf(buf,"arg_read1=%4.1f (one each)",(float)msg->readSum/(float)msg->times);
    appendStatisticsMsg(buf);
    sprintf(buf,"arg_read2=%4.1f (n/s)",(float)msg->readSum/((float)msg->usedtimeSum/1000));
    appendStatisticsMsg(buf);

    appendStatisticsMsg("------------caculator  end ------------");

    /*QTextCursor cs=ui.chat_edit->textCursor();
                cs.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
                cs.movePosition(QTextCursor::NextBlock,QTextCursor::KeepAnchor, iLines);
                cs.removeSelectedText();
          qt qtextbrowser 添加字符
*/
}
void Spo2Window::showData(char* buf){
    QTextCursor cursor =  ui->pMsg_Txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pMsg_Txt->setTextCursor(cursor);
    ui->pMsg_Txt->insertPlainText(buf);
}
void Spo2Window::appendStatisticsMsg(char* buf){
    QTextCursor cursor =  ui->pStatistics_txt->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->pStatistics_txt->setTextCursor(cursor);
    ui->pStatistics_txt->append(buf);
}
