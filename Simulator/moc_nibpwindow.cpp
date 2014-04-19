/****************************************************************************
** Meta object code from reading C++ file 'nibpwindow.h'
**
** Created: Sun Apr 20 00:37:04 2014
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nibpwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nibpwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_NibpWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x0a,
      53,   11,   11,   11, 0x0a,
      71,   11,   11,   11, 0x0a,
      84,   11,   11,   11, 0x0a,
     107,  101,   11,   11, 0x0a,
     139,  101,   11,   11, 0x0a,
     177,  101,   11,   11, 0x0a,
     216,  212,   11,   11, 0x0a,
     243,  212,   11,   11, 0x0a,
     265,   11,   11,   11, 0x0a,
     282,   11,   11,   11, 0x0a,
     302,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_NibpWindow[] = {
    "NibpWindow\0\0clear_click()\0exit_click()\0"
    "freOk_click()\0freCancel_click()\0"
    "rcOk_click()\0rcCancel_click()\0state\0"
    "startTestCheckStateChanged(int)\0"
    "genarateNewDataCheckStateChanged(int)\0"
    "showReadDataCheckStateChanged(int)\0"
    "buf\0appendStatisticsMsg(char*)\0"
    "showData(const char*)\0connectNetwork()\0"
    "disConnectNetwork()\0sendTestData()\0"
};

const QMetaObject NibpWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NibpWindow,
      qt_meta_data_NibpWindow, 0 }
};

const QMetaObject *NibpWindow::metaObject() const
{
    return &staticMetaObject;
}

void *NibpWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NibpWindow))
	return static_cast<void*>(const_cast< NibpWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int NibpWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clear_click(); break;
        case 1: exit_click(); break;
        case 2: freOk_click(); break;
        case 3: freCancel_click(); break;
        case 4: rcOk_click(); break;
        case 5: rcCancel_click(); break;
        case 6: startTestCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: genarateNewDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: showReadDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: appendStatisticsMsg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 10: showData((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 11: connectNetwork(); break;
        case 12: disConnectNetwork(); break;
        case 13: sendTestData(); break;
        }
        _id -= 14;
    }
    return _id;
}
