#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mgrdev.h"
#include "spo2window.h"
#include "nibpwindow.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent( QCloseEvent * event );

public Q_SLOTS:
    void start_click();
    void stop_click();
    void spo2_click();
    void nibp_click();
    void exit_click();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    Spo2Window* m_spo2Ui;
    NibpWindow* m_nibpUi;
};

#endif // MAINWINDOW_H
