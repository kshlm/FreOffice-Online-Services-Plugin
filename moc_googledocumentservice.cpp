/****************************************************************************
** Meta object code from reading C++ file 'googledocumentservice.h'
**
** Created: Wed Jul 14 10:32:38 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "googledocumentservice.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googledocumentservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GoogleDocumentService[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   23,   22,   22, 0x05,
      55,   22,   22,   22, 0x05,
      70,   22,   22,   22, 0x05,
      89,   22,   22,   22, 0x05,
     127,  106,   22,   22, 0x05,
     159,  106,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     202,  189,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GoogleDocumentService[] = {
    "GoogleDocumentService\0\0success\0"
    "userAuthenticated(bool)\0listDone(bool)\0"
    "downloadDone(bool)\0uploadDone(bool)\0"
    "bytesSent,bytesTotal\0"
    "downloadProgress(qint64,qint64)\0"
    "uploadProgress(qint64,qint64)\0"
    "networkReply\0handleNetworkData(QNetworkReply*)\0"
};

const QMetaObject GoogleDocumentService::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GoogleDocumentService,
      qt_meta_data_GoogleDocumentService, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GoogleDocumentService::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GoogleDocumentService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GoogleDocumentService::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GoogleDocumentService))
        return static_cast<void*>(const_cast< GoogleDocumentService*>(this));
    return QObject::qt_metacast(_clname);
}

int GoogleDocumentService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: userAuthenticated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: listDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: downloadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: uploadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: uploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: handleNetworkData((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GoogleDocumentService::userAuthenticated(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GoogleDocumentService::listDone(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GoogleDocumentService::downloadDone(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GoogleDocumentService::uploadDone(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GoogleDocumentService::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GoogleDocumentService::uploadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
