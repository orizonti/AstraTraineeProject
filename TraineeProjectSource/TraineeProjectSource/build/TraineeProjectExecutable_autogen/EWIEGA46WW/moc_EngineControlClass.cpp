/****************************************************************************
** Meta object code from reading C++ file 'EngineControlClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EngineControlClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EngineControlClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EngineControlClass_t {
    QByteArrayData data[9];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EngineControlClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EngineControlClass_t qt_meta_stringdata_EngineControlClass = {
    {
QT_MOC_LITERAL(0, 0, 18), // "EngineControlClass"
QT_MOC_LITERAL(1, 19, 14), // "SlotMoveOnStep"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "QPair<double,double>"
QT_MOC_LITERAL(4, 56, 10), // "StepVector"
QT_MOC_LITERAL(5, 67, 20), // "SlotMoveWithVelocity"
QT_MOC_LITERAL(6, 88, 9), // "VelVector"
QT_MOC_LITERAL(7, 98, 24), // "SlotMoveWithAcceleration"
QT_MOC_LITERAL(8, 123, 11) // "AccelVector"

    },
    "EngineControlClass\0SlotMoveOnStep\0\0"
    "QPair<double,double>\0StepVector\0"
    "SlotMoveWithVelocity\0VelVector\0"
    "SlotMoveWithAcceleration\0AccelVector"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EngineControlClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       7,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void, 0x80000000 | 3,    8,

       0        // eod
};

void EngineControlClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EngineControlClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotMoveOnStep((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        case 1: _t->SlotMoveWithVelocity((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        case 2: _t->SlotMoveWithAcceleration((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EngineControlClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EngineControlClass.data,
    qt_meta_data_EngineControlClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EngineControlClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EngineControlClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EngineControlClass.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int EngineControlClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
