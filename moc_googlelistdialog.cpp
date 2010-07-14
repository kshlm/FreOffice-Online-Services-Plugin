/****************************************************************************
** Meta object code from reading C++ file 'googlelistdialog.h'
**
** Created: Wed Jul 14 10:32:42 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "googlelistdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'googlelistdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_googleListDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      46,   17,   17,   17, 0x08,
      72,   17,   17,   17, 0x08,
      87,   17,   17,   17, 0x08,
     112,  110,   17,   17, 0x08,
     145,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_googleListDialog[] = {
    "googleListDialog\0\0downloadButtonClickedSlot()\0"
    "uploadButtonClickedSlot()\0fillList(bool)\0"
    "downloadDoneSlot(bool)\0,\0"
    "updateProgressBar(qint64,qint64)\0"
    "refreshList()\0"
};

const QMetaObject googleListDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_googleListDialog,
      qt_meta_data_googleListDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &googleListDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *googleListDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *googleListDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_googleListDialog))
        return static_cast<void*>(const_cast< googleListDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int googleListDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: downloadButtonClickedSlot(); break;
        case 1: uploadButtonClickedSlot(); break;
        case 2: fillList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: downloadDoneSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: updateProgressBar((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: refreshList(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
