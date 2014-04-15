/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Apr 15 22:13:17 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pExit_btn;
    QTextBrowser *pConnectMsg_txt;
    QTextBrowser *pDisplay_txt;
    QPushButton *pClearCon_btn;
    QPushButton *pClearDisplay_btn;
    QLabel *pStart_label;
    QPushButton *pStart_btn;
    QPushButton *pStop_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 400);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pExit_btn = new QPushButton(centralWidget);
        pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
        pExit_btn->setGeometry(QRect(390, 280, 99, 32));
        pConnectMsg_txt = new QTextBrowser(centralWidget);
        pConnectMsg_txt->setObjectName(QString::fromUtf8("pConnectMsg_txt"));
        pConnectMsg_txt->setGeometry(QRect(20, 60, 171, 201));
        pDisplay_txt = new QTextBrowser(centralWidget);
        pDisplay_txt->setObjectName(QString::fromUtf8("pDisplay_txt"));
        pDisplay_txt->setGeometry(QRect(200, 60, 256, 201));
        pClearCon_btn = new QPushButton(centralWidget);
        pClearCon_btn->setObjectName(QString::fromUtf8("pClearCon_btn"));
        pClearCon_btn->setGeometry(QRect(20, 280, 99, 32));
        pClearDisplay_btn = new QPushButton(centralWidget);
        pClearDisplay_btn->setObjectName(QString::fromUtf8("pClearDisplay_btn"));
        pClearDisplay_btn->setGeometry(QRect(230, 280, 99, 32));
        pStart_label = new QLabel(centralWidget);
        pStart_label->setObjectName(QString::fromUtf8("pStart_label"));
        pStart_label->setGeometry(QRect(160, 20, 151, 22));
        pStart_btn = new QPushButton(centralWidget);
        pStart_btn->setObjectName(QString::fromUtf8("pStart_btn"));
        pStart_btn->setGeometry(QRect(20, 10, 99, 32));
        pStop_btn = new QPushButton(centralWidget);
        pStop_btn->setObjectName(QString::fromUtf8("pStop_btn"));
        pStop_btn->setGeometry(QRect(340, 10, 99, 32));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pExit_btn->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        pClearCon_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pClearDisplay_btn->setText(QApplication::translate("MainWindow", "clear", 0, QApplication::UnicodeUTF8));
        pStart_label->setText(QApplication::translate("MainWindow", "server is not start", 0, QApplication::UnicodeUTF8));
        pStart_btn->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
        pStop_btn->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
