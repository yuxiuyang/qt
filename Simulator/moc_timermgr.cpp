/****************************************************************************
** Meta object code from reading C++ file 'timermgr.h'
**
** Created: Sat Jan 18 15:09:22 2014
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "timermgr.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timermgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TimerMgr[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TimerMgr[] = {
    "TimerMgr\0\0_onWriteTimeout()\0"
};

const QMetaObject TimerMgr::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TimerMgr,
      qt_meta_data_TimerMgr, 0 }
};

const QMetaObject *TimerMgr::metaObject() const
{
    return &staticMetaObject;
}

void *TimerMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TimerMgr))
	return static_cast<void*>(const_cast< TimerMgr*>(this));
    return QThread::qt_metacast(_clname);
}

int TimerMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
