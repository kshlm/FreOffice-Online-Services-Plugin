/****************************************************************************
** Meta object code from reading C++ file 'googleuploaddialog.h'
**
** Created: Wed Jul 14 10:32:42 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "googleuploaddialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googleuploaddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_googleUploadDialog[] = {

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
      41,   20,   19,   19, 0x08,
      75,   19,   19,   19, 0x08,
      92,   19,   19,   19, 0x08,
     118,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_googleUploadDialog[] = {
    "googleUploadDialog\0\0bytesSent,bytesTotal\0"
    "uploadProgressSlot(qint64,qint64)\0"
    "showFileDialog()\0uploadButtonClickedSlot()\0"
    "uploadDoneSlot(bool)\0"
};

const QMetaObject googleUploadDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_googleUploadDialog,
      qt_meta_data_googleUploadDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &googleUploadDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *googleUploadDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *googleUploadDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_googleUploadDialog))
        return static_cast<void*>(const_cast< googleUploadDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int googleUploadDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: uploadProgressSlot((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: showFileDialog(); break;
        case 2: uploadButtonClickedSlot(); break;
        case 3: uploadDoneSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
