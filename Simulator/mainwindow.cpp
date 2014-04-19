#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <stdio.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_spo2Ui = new Spo2Window();
    m_spo2Ui->setObject(this);

    m_nibpUi = new NibpWindow();
    m_nibpUi->setObject(this);

    connect(ui->pStart_btn, SIGNAL(clicked()), this, SLOT(start_click()));
    connect(ui->pStop_btn, SIGNAL(clicked()), this, SLOT(stop_click()));
    connect(ui->pSpo2_btn, SIGNAL(clicked()), this, SLOT(spo2_click()));
    connect(ui->pNibp_btn, SIGNAL(clicked()), this, SLOT(nibp_click()));
    connect(ui->pExit_btn,SIGNAL(clicked()),this,SLOT(exit_click()));

    ui->pStop_btn->setEnabled(false);
    move(400,100);
    resize(width()+30,height());
}

MainWindow::~MainWindow()
{
    if(m_spo2Ui){
        m_spo2Ui->hide();
        cout<<"m_spo2Ui->hide();"<<endl;
        m_spo2Ui->close();
        delete m_spo2Ui;
        m_spo2Ui=NULL;
    }

    if(m_nibpUi){
        m_nibpUi->hide();
        cout<<"m_nibpUi->hide();"<<endl;
        m_nibpUi->close();
        delete m_nibpUi;
        m_nibpUi=NULL;
    }

cout<<"~MainWindow"<<endl;
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
void MainWindow::closeEvent( QCloseEvent * event )
{
    m_spo2Ui->hide();
    m_nibpUi->hide();
    event->accept();
//    switch( QMessageBox::information( this, tr("Comfirm:"),
//  tr("Do you really close window?"),
//  tr("Yes"), tr("No"),
//  0, 1 ) )
//{
//    case 0:
//  m_spo2Ui->hide();
//  event->accept();
//        break;
//    case 1:
//default:
//        event->ignore();
//        break;
//}
}

void MainWindow::start_click(){
    ui->pStart_btn->setEnabled(false);
    ui->pStop_btn->setEnabled(true);

    ui->pMsg_Txt->append("start...");

    char buf[100];
    sprintf(buf,"start threadid=%lu",pthread_self());
    ui->pMsg_Txt->append(buf);

    MgrDev::getInstance()->start();
}

void MainWindow::stop_click(){
    ui->pStart_btn->setEnabled(true);
    ui->pStop_btn->setEnabled(false);
    ui->pMsg_Txt->append("stop...");

    char buf[100];
    sprintf(buf,"stop threadid=%lu",pthread_self());
    ui->pMsg_Txt->append(buf);

    MgrDev::getInstance()->stop();
}

void MainWindow::spo2_click(){
    if(m_spo2Ui->isVisible()){
        m_spo2Ui->hide();
    }
    m_spo2Ui->move(x(),y());
    m_spo2Ui->resize(width(),height());
    m_spo2Ui->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    m_spo2Ui->show();
    setWindowTitle("Spo2 Window");
}
void MainWindow::nibp_click(){
    if(m_nibpUi->isVisible()){
        m_nibpUi->hide();
    }
    m_nibpUi->move(x(),y());
    m_nibpUi->resize(width(),height());
    m_nibpUi->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    m_nibpUi->show();
    setWindowTitle("Nibp Window");
}
void MainWindow::exit_click(){
    close();
}
