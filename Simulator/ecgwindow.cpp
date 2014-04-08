#include "ecgwindow.h"
#include "ui_ecgwindow.h"

EcgWindow::EcgWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EcgWindow)
{
    ui->setupUi(this);
}

EcgWindow::~EcgWindow()
{
    delete ui;
}

void EcgWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
