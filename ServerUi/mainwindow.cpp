#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pStart_btn, SIGNAL(clicked()), this, SLOT(start_click()));
    connect(ui->pStop_btn, SIGNAL(clicked()), this, SLOT(stop_click()));
    connect(ui->pClearCon_btn, SIGNAL(clicked()), this, SLOT(clearConnectMsg_click()));
    connect(ui->pClearDisplay_btn, SIGNAL(clicked()), this, SLOT(clearDisplayMsg_click()));
    connect(ui->pExit_btn,SIGNAL(clicked()),this,SLOT(exit_click()));
    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);


    m_pDataMgr = new DataMgr();
    m_pLinkMgr = new LinkMgr();
    m_pLinkMgr->setWindow((void*)this);

    DataDev::getInstance()->m_pLinkMgr = m_pLinkMgr;
    DataDev::getInstance()->m_pDataMgr = m_pDataMgr;
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
    DataDev::getInstance()->terminate();
}

void MainWindow::clearConnectMsg_click(){
    ui->pConnectMsg_txt->clear();
}

void MainWindow::clearDisplayMsg_click(){
    ui->pDisplay_txt->clear();
}
void MainWindow::appendMsg(char* msg){
    ui->pConnectMsg_txt->append(msg);
}
void MainWindow::exit_click(){
    close();
}
