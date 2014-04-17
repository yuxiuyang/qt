/********************************************************************************
** Form generated from reading ui file 'spo2window.ui'
**
** Created: Thu Apr 17 21:25:20 2014
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SPO2WINDOW_H
#define UI_SPO2WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_Spo2Window
{
public:
    QPushButton *pExit_btn;
    QPushButton *pClear_btn;
    QFrame *test;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *pFre_edit;
    QTextEdit *pTm_edit;
    QTextEdit *pRc_edit;
    QPushButton *pFreOk_btn;
    QPushButton *pRcCancel_btn;
    QPushButton *pFreCancel_btn;
    QPushButton *pRcOk_btn;
    QCheckBox *pST_check;
    QTextBrowser *pStatistics_txt;
    QCheckBox *pShowReadData_check;
    QTextBrowser *pMsg_Txt;
    QCheckBox *pGenerateData_check;
    QPushButton *pConnect_btn;
    QPushButton *pSendTestData_btn;
    QPushButton *pDisConnect_btn;

    void setupUi(QWidget *Spo2Window)
    {
    if (Spo2Window->objectName().isEmpty())
        Spo2Window->setObjectName(QString::fromUtf8("Spo2Window"));
    Spo2Window->resize(685, 398);
    pExit_btn = new QPushButton(Spo2Window);
    pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
    pExit_btn->setGeometry(QRect(520, 20, 99, 32));
    pClear_btn = new QPushButton(Spo2Window);
    pClear_btn->setObjectName(QString::fromUtf8("pClear_btn"));
    pClear_btn->setGeometry(QRect(400, 20, 99, 32));
    test = new QFrame(Spo2Window);
    test->setObjectName(QString::fromUtf8("test"));
    test->setGeometry(QRect(30, 190, 591, 201));
    test->setFrameShape(QFrame::StyledPanel);
    test->setFrameShadow(QFrame::Raised);
    label = new QLabel(test);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 50, 76, 21));
    label_2 = new QLabel(test);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(10, 90, 76, 22));
    label_3 = new QLabel(test);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(10, 130, 81, 22));
    pFre_edit = new QTextEdit(test);
    pFre_edit->setObjectName(QString::fromUtf8("pFre_edit"));
    pFre_edit->setGeometry(QRect(100, 50, 104, 31));
    pFre_edit->setFocusPolicy(Qt::WheelFocus);
    pFre_edit->setContextMenuPolicy(Qt::DefaultContextMenu);
    pTm_edit = new QTextEdit(test);
    pTm_edit->setObjectName(QString::fromUtf8("pTm_edit"));
    pTm_edit->setGeometry(QRect(100, 90, 104, 31));
    pTm_edit->setFocusPolicy(Qt::WheelFocus);
    pTm_edit->setContextMenuPolicy(Qt::DefaultContextMenu);
    pRc_edit = new QTextEdit(test);
    pRc_edit->setObjectName(QString::fromUtf8("pRc_edit"));
    pRc_edit->setGeometry(QRect(100, 130, 104, 31));
    pRc_edit->setFocusPolicy(Qt::WheelFocus);
    pRc_edit->setContextMenuPolicy(Qt::DefaultContextMenu);
    pFreOk_btn = new QPushButton(test);
    pFreOk_btn->setObjectName(QString::fromUtf8("pFreOk_btn"));
    pFreOk_btn->setGeometry(QRect(210, 50, 51, 32));
    pRcCancel_btn = new QPushButton(test);
    pRcCancel_btn->setObjectName(QString::fromUtf8("pRcCancel_btn"));
    pRcCancel_btn->setGeometry(QRect(270, 130, 51, 32));
    pFreCancel_btn = new QPushButton(test);
    pFreCancel_btn->setObjectName(QString::fromUtf8("pFreCancel_btn"));
    pFreCancel_btn->setGeometry(QRect(270, 50, 51, 32));
    pRcOk_btn = new QPushButton(test);
    pRcOk_btn->setObjectName(QString::fromUtf8("pRcOk_btn"));
    pRcOk_btn->setGeometry(QRect(210, 130, 51, 32));
    pST_check = new QCheckBox(test);
    pST_check->setObjectName(QString::fromUtf8("pST_check"));
    pST_check->setGeometry(QRect(10, 10, 111, 27));
    pStatistics_txt = new QTextBrowser(test);
    pStatistics_txt->setObjectName(QString::fromUtf8("pStatistics_txt"));
    pStatistics_txt->setGeometry(QRect(330, 20, 251, 171));
    pStatistics_txt->setReadOnly(true);
    pShowReadData_check = new QCheckBox(test);
    pShowReadData_check->setObjectName(QString::fromUtf8("pShowReadData_check"));
    pShowReadData_check->setGeometry(QRect(140, 10, 141, 27));
    pMsg_Txt = new QTextBrowser(Spo2Window);
    pMsg_Txt->setObjectName(QString::fromUtf8("pMsg_Txt"));
    pMsg_Txt->setEnabled(true);
    pMsg_Txt->setGeometry(QRect(30, 20, 361, 161));
    pMsg_Txt->setReadOnly(false);
    pMsg_Txt->setOpenExternalLinks(true);
    pGenerateData_check = new QCheckBox(Spo2Window);
    pGenerateData_check->setObjectName(QString::fromUtf8("pGenerateData_check"));
    pGenerateData_check->setGeometry(QRect(410, 160, 161, 22));
    pConnect_btn = new QPushButton(Spo2Window);
    pConnect_btn->setObjectName(QString::fromUtf8("pConnect_btn"));
    pConnect_btn->setGeometry(QRect(400, 70, 111, 32));
    pSendTestData_btn = new QPushButton(Spo2Window);
    pSendTestData_btn->setObjectName(QString::fromUtf8("pSendTestData_btn"));
    pSendTestData_btn->setGeometry(QRect(400, 120, 221, 31));
    pDisConnect_btn = new QPushButton(Spo2Window);
    pDisConnect_btn->setObjectName(QString::fromUtf8("pDisConnect_btn"));
    pDisConnect_btn->setGeometry(QRect(530, 70, 91, 32));

    retranslateUi(Spo2Window);

    QMetaObject::connectSlotsByName(Spo2Window);
    } // setupUi

    void retranslateUi(QWidget *Spo2Window)
    {
    Spo2Window->setWindowTitle(QApplication::translate("Spo2Window", "SPO2 Window", 0, QApplication::UnicodeUTF8));
    pExit_btn->setText(QApplication::translate("Spo2Window", "exit", 0, QApplication::UnicodeUTF8));
    pClear_btn->setText(QApplication::translate("Spo2Window", "clear", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("Spo2Window", "freqence", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("Spo2Window", "timeout", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("Spo2Window", "readcount", 0, QApplication::UnicodeUTF8));
    pFreOk_btn->setText(QApplication::translate("Spo2Window", "ok", 0, QApplication::UnicodeUTF8));
    pRcCancel_btn->setText(QApplication::translate("Spo2Window", "cancel", 0, QApplication::UnicodeUTF8));
    pFreCancel_btn->setText(QApplication::translate("Spo2Window", "cancel", 0, QApplication::UnicodeUTF8));
    pRcOk_btn->setText(QApplication::translate("Spo2Window", "ok", 0, QApplication::UnicodeUTF8));
    pST_check->setText(QApplication::translate("Spo2Window", "start to test", 0, QApplication::UnicodeUTF8));
    pShowReadData_check->setText(QApplication::translate("Spo2Window", "show read data", 0, QApplication::UnicodeUTF8));
    pGenerateData_check->setText(QApplication::translate("Spo2Window", "generate new data", 0, QApplication::UnicodeUTF8));
    pConnect_btn->setText(QApplication::translate("Spo2Window", "connect", 0, QApplication::UnicodeUTF8));
    pSendTestData_btn->setText(QApplication::translate("Spo2Window", "sendTestData", 0, QApplication::UnicodeUTF8));
    pDisConnect_btn->setText(QApplication::translate("Spo2Window", "disconnect", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Spo2Window);
    } // retranslateUi

};

namespace Ui {
    class Spo2Window: public Ui_Spo2Window {};
} // namespace Ui

#endif // UI_SPO2WINDOW_H
