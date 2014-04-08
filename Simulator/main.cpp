#include <QtGui/QApplication>
#include "mainwindow.h"
//#include "spo2mgr.h"
int main(int argc, char *argv[])
{
    //Spo2Mgr spo2Mgr;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
