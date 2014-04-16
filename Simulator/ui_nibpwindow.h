/********************************************************************************
** Form generated from reading ui file 'nibpwindow.ui'
**
** Created: Wed Apr 16 22:19:41 2014
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NIBPWINDOW_H
#define UI_NIBPWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>

class Ui_NibpWindow
{
public:
    QTextBrowser *pMsg_Txt;
    QPushButton *pExit_btn;
    QPushButton *pClear_btn;
    QPushButton *pSendTestData_btn;
    QCheckBox *pGenerateData_check;
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
    QPushButton *pConnect_btn;
    QPushButton *pDisConnect_btn;

    void setupUi(QDialog *NibpWindow)
    {
    if (NibpWindow->objectName().isEmpty())
        NibpWindow->setObjectName(QString::fromUtf8("NibpWindow"));
    NibpWindow->resize(627, 482);
    pMsg_Txt = new QTextBrowser(NibpWindow);
    pMsg_Txt->setObjectName(QString::fromUtf8("pMsg_Txt"));
    pMsg_Txt->setEnabled(true);
    pMsg_Txt->setGeometry(QRect(30, 20, 361, 161));
    pMsg_Txt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    pMsg_Txt->setAutoFormatting(QTextEdit::AutoNone);
    pMsg_Txt->setReadOnly(false);
    pExit_btn = new QPushButton(NibpWindow);
    pExit_btn->setObjectName(QString::fromUtf8("pExit_btn"));
    pExit_btn->setGeometry(QRect(520, 20, 99, 32));
    pClear_btn = new QPushButton(NibpWindow);
    pClear_btn->setObjectName(QString::fromUtf8("pClear_btn"));
    pClear_btn->setGeometry(QRect(400, 20, 99, 32));
    pSendTestData_btn = new QPushButton(NibpWindow);
    pSendTestData_btn->setObjectName(QString::fromUtf8("pSendTestData_btn"));
    pSendTestData_btn->setGeometry(QRect(400, 120, 221, 31));
    pGenerateData_check = new QCheckBox(NibpWindow);
    pGenerateData_check->setObjectName(QString::fromUtf8("pGenerateData_check"));
    pGenerateData_check->setGeometry(QRect(410, 160, 161, 22));
    test = new QFrame(NibpWindow);
    test->setObjectName(QString::fromUtf8("test"));
    test->setGeometry(QRect(30, 210, 591, 201));
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
    pShowReadData_check = new QCheckBox(test);
    pShowReadData_check->setObjectName(QString::fromUtf8("pShowReadData_check"));
    pShowReadData_check->setGeometry(QRect(140, 10, 141, 27));
    pConnect_btn = new QPushButton(NibpWindow);
    pConnect_btn->setObjectName(QString::fromUtf8("pConnect_btn"));
    pConnect_btn->setGeometry(QRect(400, 70, 111, 32));
    pDisConnect_btn = new QPushButton(NibpWindow);
    pDisConnect_btn->setObjectName(QString::fromUtf8("pDisConnect_btn"));
    pDisConnect_btn->setGeometry(QRect(520, 70, 91, 32));

    retranslateUi(NibpWindow);

    QMetaObject::connectSlotsByName(NibpWindow);
    } // setupUi

    void retranslateUi(QDialog *NibpWindow)
    {
    NibpWindow->setWindowTitle(QApplication::translate("NibpWindow", "Dialog", 0, QApplication::UnicodeUTF8));
    pExit_btn->setText(QApplication::translate("NibpWindow", "exit", 0, QApplication::UnicodeUTF8));
    pClear_btn->setText(QApplication::translate("NibpWindow", "clear", 0, QApplication::UnicodeUTF8));
    pSendTestData_btn->setText(QApplication::translate("NibpWindow", "sendTestData", 0, QApplication::UnicodeUTF8));
    pGenerateData_check->setText(QApplication::translate("NibpWindow", "generate new data", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("NibpWindow", "freqence", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("NibpWindow", "timeout", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("NibpWindow", "readcount", 0, QApplication::UnicodeUTF8));
    pFreOk_btn->setText(QApplication::translate("NibpWindow", "ok", 0, QApplication::UnicodeUTF8));
    pRcCancel_btn->setText(QApplication::translate("NibpWindow", "cancel", 0, QApplication::UnicodeUTF8));
    pFreCancel_btn->setText(QApplication::translate("NibpWindow", "cancel", 0, QApplication::UnicodeUTF8));
    pRcOk_btn->setText(QApplication::translate("NibpWindow", "ok", 0, QApplication::UnicodeUTF8));
    pST_check->setText(QApplication::translate("NibpWindow", "start to test", 0, QApplication::UnicodeUTF8));
    pShowReadData_check->setText(QApplication::translate("NibpWindow", "show read data", 0, QApplication::UnicodeUTF8));
    pConnect_btn->setText(QApplication::translate("NibpWindow", "connect", 0, QApplication::UnicodeUTF8));
    pDisConnect_btn->setText(QApplication::translate("NibpWindow", "disconnect", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(NibpWindow);
    } // retranslateUi

};

namespace Ui {
    class NibpWindow: public Ui_NibpWindow {};
} // namespace Ui

#endif // UI_NIBPWINDOW_H
