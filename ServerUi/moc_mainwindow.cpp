/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun Apr 20 00:36:19 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x0a,
      52,   11,   11,   11, 0x0a,
      76,   11,   11,   11, 0x0a,
     104,  100,   11,   11, 0x0a,
     127,  100,   11,   11, 0x0a,
     159,  151,   11,   11, 0x0a,
     187,   11,   11,   11, 0x0a,
     213,   11,  201,   11, 0x0a,
     229,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0start_click()\0stop_click()\0"
    "exit_click()\0clearConnectMsg_click()\0"
    "clearDisplayMsg_click()\0msg\0"
    "appendMsg(const char*)\0appendData(const char*)\0"
    "msg,len\0appendData(const BYTE*,int)\0"
    "radioChange()\0ClientType_\0getClientType()\0"
    "sendTimer()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start_click(); break;
        case 1: stop_click(); break;
        case 2: exit_click(); break;
        case 3: clearConnectMsg_click(); break;
        case 4: clearDisplayMsg_click(); break;
        case 5: appendMsg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 6: appendData((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 7: appendData((*reinterpret_cast< const BYTE*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 8: radioChange(); break;
        case 9: { ClientType_ _r = getClientType();
            if (_a[0]) *reinterpret_cast< ClientType_*>(_a[0]) = _r; }  break;
        case 10: sendTimer(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
