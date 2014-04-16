#ifndef SPO2WINDOW_H
#define SPO2WINDOW_H

//#include <QWidget>
#include <QDialog>
#include "spo2mgr.h"
#include <QTimer>
#include <QMutex>
namespace Ui {
    class Spo2Window;
}

//class Spo2Window : public QWidget {
class Spo2Window : public QDialog {
    Q_OBJECT
public:
    Spo2Window(QWidget *parent = 0);
    ~Spo2Window();
    void setObject(QWidget* object){
        m_object=object;
    }
public Q_SLOTS:
    void clear_click();
    void exit_click();

    void freOk_click();
    void freCancel_click();
    void rcOk_click();
    void rcCancel_click();

    void startTestCheckStateChanged (int state);
    void genarateNewDataCheckStateChanged(int state);
    void showReadDataCheckStateChanged(int state);
    void showData(char* buf);
    void appendStatisticsMsg(char* buf);
    void connectNetwork();
    void disConnectNetwork();
    void sendTestData();

public:
    //display Statistics result
    void displayStatisicsResult();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::Spo2Window *ui;
    QWidget* m_object;

    Spo2Mgr* m_spo2Mgr;
};

#endif // SPO2WINDOW_H
