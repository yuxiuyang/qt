/****************************************************************************
** Meta object code from reading C++ file 'ecgwindow.h'
**
** Created: Thu Apr 17 21:25:37 2014
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ecgwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ecgwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_EcgWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_EcgWindow[] = {
    "EcgWindow\0"
};

const QMetaObject EcgWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EcgWindow,
      qt_meta_data_EcgWindow, 0 }
};

const QMetaObject *EcgWindow::metaObject() const
{
    return &staticMetaObject;
}

void *EcgWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EcgWindow))
	return static_cast<void*>(const_cast< EcgWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int EcgWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
