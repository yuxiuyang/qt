/********************************************************************************
** Form generated from reading ui file 'ecgwindow.ui'
**
** Created: Wed Apr 16 19:40:15 2014
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ECGWINDOW_H
#define UI_ECGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>

class Ui_EcgWindow
{
public:

    void setupUi(QDialog *EcgWindow)
    {
    if (EcgWindow->objectName().isEmpty())
        EcgWindow->setObjectName(QString::fromUtf8("EcgWindow"));
    EcgWindow->resize(400, 300);

    retranslateUi(EcgWindow);

    QMetaObject::connectSlotsByName(EcgWindow);
    } // setupUi

    void retranslateUi(QDialog *EcgWindow)
    {
    EcgWindow->setWindowTitle(QApplication::translate("EcgWindow", "Dialog", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(EcgWindow);
    } // retranslateUi

};

namespace Ui {
    class EcgWindow: public Ui_EcgWindow {};
} // namespace Ui

#endif // UI_ECGWINDOW_H
