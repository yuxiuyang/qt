/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Feb 13 14:55:17 2014
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
    QPushButton *pStart_btn;
    QPushButton *pStop_btn;
    QTextBrowser *pMsg_Txt;
    QPushButton *pSpo2_btn;
    QPushButton *pExit_btn;
    QPushButton *pNibp_btn;
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
        pStart_btn = new QPushButton(centralWidget);
        pStart_btn->setObjectName(QString::fromUtf8("pStart_btn"));
        pStart_btn->setGeometry(QRect(120, 230, 99, 32));
        pStop_btn = new QPushButton(centralWidget);
        pStop_btn->setObjectName(QString::fromUtf8("pStop_btn"));
        pStop_btn->setGeometry(QRect(360, 230, 99, 32));
        pMsg_Txt = new QTextBrowser(centralWidget);
        pMsg_Txt->setObjectName(QString::fromUtf8("pMsg_Txt"));
        pMsg_Txt->setGeometry(QRect(120, 50, 341, 141));
        pSpo2_btn = new QPushButton(centralWidget);
        pSpo2_btn->setObjectName(QString::fromUtf8("pSpo2_btn"));
        pSpo2_btn->setGeometry(QRect(120, 280, 99, 32));
        pExit_btn = new QPushButton(centralWidget);
        pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
        pExit_btn->setGeometry(QRect(490, 30, 99, 32));
        pNibp_btn = new QPushButton(centralWidget);
        pNibp_btn->setObjectName(QString::fromUtf8("pNibp_btn"));
        pNibp_btn->setGeometry(QRect(240, 280, 99, 32));
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
        pStart_btn->setText(QApplication::translate("MainWindow", "start", 0, QApplication::UnicodeUTF8));
        pStop_btn->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        pSpo2_btn->setText(QApplication::translate("MainWindow", "spo2", 0, QApplication::UnicodeUTF8));
        pExit_btn->setText(QApplication::translate("MainWindow", "exit", 0, QApplication::UnicodeUTF8));
        pNibp_btn->setText(QApplication::translate("MainWindow", "nibp", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
