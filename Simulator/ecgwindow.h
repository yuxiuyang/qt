#ifndef ECGWINDOW_H
#define ECGWINDOW_H

#include <QDialog>

namespace Ui {
    class EcgWindow;
}

class EcgWindow : public QDialog {
    Q_OBJECT
public:
    EcgWindow(QWidget *parent = 0);
    ~EcgWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::EcgWindow *ui;
};

#endif // ECGWINDOW_H
