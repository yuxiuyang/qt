#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network_server.h"
#include "../common/datadev.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public Q_SLOTS:
    void start_click();
    void stop_click();
    void exit_click();
    void clearConnectMsg_click();
    void clearDisplayMsg_click();

    void appendMsg(const char* msg);
    void appendMsg(ClientType_ type,char* msg);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;


    DataMgr* m_pDataMgr;
    DataDev* m_pDataDev;
    LinkMgr* m_pLinkMgr;


    ClientType_ m_dataType;
};

#endif // MAINWINDOW_H
