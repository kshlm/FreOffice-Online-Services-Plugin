/****************************************************************************
** Meta object code from reading C++ file 'slideshare.h'
**
** Created: Wed Jul 14 10:32:39 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "slideshare.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'slideshare.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SlideShare[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      33,   12,   11,   11, 0x05,
      65,   12,   11,   11, 0x05,
      95,   11,   11,   11, 0x05,
     111,   11,   11,   11, 0x05,
     124,   11,   11,   11, 0x05,
     135,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     150,   11,   11,   11, 0x08,
     163,   11,   11,   11, 0x08,
     175,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SlideShare[] = {
    "SlideShare\0\0bytesSent,bytesTotal\0"
    "downloadProgress(qint64,qint64)\0"
    "uploadProgress(qint64,qint64)\0"
    "loginDone(bool)\0uploadDone()\0listDone()\0"
    "downloadDone()\0afterLogin()\0parseList()\0"
    "saveFile()\0"
};

const QMetaObject SlideShare::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SlideShare,
      qt_meta_data_SlideShare, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SlideShare::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SlideShare::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SlideShare::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SlideShare))
        return static_cast<void*>(const_cast< SlideShare*>(this));
    return QObject::qt_metacast(_clname);
}

int SlideShare::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: uploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 2: loginDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: uploadDone(); break;
        case 4: listDone(); break;
        case 5: downloadDone(); break;
        case 6: afterLogin(); break;
        case 7: parseList(); break;
        case 8: saveFile(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SlideShare::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SlideShare::uploadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SlideShare::loginDone(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SlideShare::uploadDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void SlideShare::listDone()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void SlideShare::downloadDone()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
