#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network_server.h"
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

    void appendMsg(char* msg);


protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Network_Server m_serverNetwork;
};

#endif // MAINWINDOW_H
