#ifndef NIBPWINDOW_H
#define NIBPWINDOW_H

#include <QDialog>
#include "nibpmgr.h"
namespace Ui {
    class NibpWindow;
}

class NibpWindow : public QDialog {
    Q_OBJECT
public:
    NibpWindow(QWidget *parent = 0);
    ~NibpWindow();

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
    void connectNetwork();
    void disConnectNetwork();
    void sendTestData();

public:
    //display Statistics result
    void displayStatisicsResult();


protected:
    void changeEvent(QEvent *e);

private:
    Ui::NibpWindow *ui;
    QWidget* m_object;

    NibpMgr* m_nibpMgr;
};

#endif // NIBPWINDOW_H
