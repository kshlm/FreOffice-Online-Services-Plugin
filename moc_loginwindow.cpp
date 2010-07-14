/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created: Wed Jul 14 11:34:00 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "loginwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      34,   28,   12,   12, 0x08,
      63,   55,   12,   12, 0x08,
      95,   83,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LoginWindow[] = {
    "LoginWindow\0\0loginService()\0index\0"
    "serviceSelected(int)\0success\0"
    "authenticated(bool)\0loginStatus\0"
    "slideShareLoginDoneSlot(bool)\0"
};

const QMetaObject LoginWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LoginWindow,
      qt_meta_data_LoginWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: loginService(); break;
        case 1: serviceSelected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: authenticated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: slideShareLoginDoneSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
