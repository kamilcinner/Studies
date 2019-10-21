/****************************************************************************
** Meta object code from reading C++ file 'wykres.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../12_cw_1/wykres.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wykres.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Wykres_t {
    QByteArrayData data[8];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Wykres_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Wykres_t qt_meta_stringdata_Wykres = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Wykres"
QT_MOC_LITERAL(1, 7, 24), // "on_toPointButton_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "on_toLineButton_clicked"
QT_MOC_LITERAL(4, 57, 25), // "on_decreaseButton_clicked"
QT_MOC_LITERAL(5, 83, 24), // "on_enlargeButton_clicked"
QT_MOC_LITERAL(6, 108, 27), // "on_clearFieldButton_clicked"
QT_MOC_LITERAL(7, 136, 29) // "on_drawNewGraphButton_clicked"

    },
    "Wykres\0on_toPointButton_clicked\0\0"
    "on_toLineButton_clicked\0"
    "on_decreaseButton_clicked\0"
    "on_enlargeButton_clicked\0"
    "on_clearFieldButton_clicked\0"
    "on_drawNewGraphButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Wykres[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Wykres::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Wykres *_t = static_cast<Wykres *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_toPointButton_clicked(); break;
        case 1: _t->on_toLineButton_clicked(); break;
        case 2: _t->on_decreaseButton_clicked(); break;
        case 3: _t->on_enlargeButton_clicked(); break;
        case 4: _t->on_clearFieldButton_clicked(); break;
        case 5: _t->on_drawNewGraphButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Wykres::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Wykres.data,
    qt_meta_data_Wykres,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Wykres::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Wykres::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Wykres.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Wykres::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
