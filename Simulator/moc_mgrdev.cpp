/****************************************************************************
** Meta object code from reading C++ file 'mgrdev.h'
**
** Created: Sat Apr 19 19:28:01 2014
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mgrdev.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mgrdev.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_MgrDev[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MgrDev[] = {
    "MgrDev\0\0_onWriteTimeout()\0"
};

const QMetaObject MgrDev::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MgrDev,
      qt_meta_data_MgrDev, 0 }
};

const QMetaObject *MgrDev::metaObject() const
{
    return &staticMetaObject;
}

void *MgrDev::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MgrDev))
	return static_cast<void*>(const_cast< MgrDev*>(this));
    return QThread::qt_metacast(_clname);
}

int MgrDev::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _onWriteTimeout(); break;
        }
        _id -= 1;
    }
    return _id;
}
