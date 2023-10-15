/****************************************************************************
** Meta object code from reading C++ file 'LaserControlClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../LaserControlClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LaserControlClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LaserControlClass_t {
    QByteArrayData data[13];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaserControlClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaserControlClass_t qt_meta_stringdata_LaserControlClass = {
    {
QT_MOC_LITERAL(0, 0, 17), // "LaserControlClass"
QT_MOC_LITERAL(1, 18, 16), // "SignalTurnLaser1"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "OnOff"
QT_MOC_LITERAL(4, 42, 16), // "SignalTurnLaser2"
QT_MOC_LITERAL(5, 59, 16), // "SignalTurnLaser3"
QT_MOC_LITERAL(6, 76, 19), // "IterateWorkingLaser"
QT_MOC_LITERAL(7, 96, 18), // "SlotSwitchFireBeam"
QT_MOC_LITERAL(8, 115, 21), // "SlotSwitchPointerBeam"
QT_MOC_LITERAL(9, 137, 19), // "SlotSwitchPilotBeam"
QT_MOC_LITERAL(10, 157, 7), // "Channel"
QT_MOC_LITERAL(11, 165, 19), // "SlotSwitchAllLasers"
QT_MOC_LITERAL(12, 185, 22) // "SlotStartIterateLasers"

    },
    "LaserControlClass\0SignalTurnLaser1\0\0"
    "OnOff\0SignalTurnLaser2\0SignalTurnLaser3\0"
    "IterateWorkingLaser\0SlotSwitchFireBeam\0"
    "SlotSwitchPointerBeam\0SlotSwitchPilotBeam\0"
    "Channel\0SlotSwitchAllLasers\0"
    "SlotStartIterateLasers"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaserControlClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   68,    2, 0x0a /* Public */,
       7,    1,   69,    2, 0x0a /* Public */,
       8,    1,   72,    2, 0x0a /* Public */,
       9,    2,   75,    2, 0x0a /* Public */,
      11,    1,   80,    2, 0x0a /* Public */,
      12,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   10,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void LaserControlClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LaserControlClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalTurnLaser1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->SignalTurnLaser2((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->SignalTurnLaser3((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->IterateWorkingLaser(); break;
        case 4: _t->SlotSwitchFireBeam((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->SlotSwitchPointerBeam((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->SlotSwitchPilotBeam((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->SlotSwitchAllLasers((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->SlotStartIterateLasers((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LaserControlClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaserControlClass::SignalTurnLaser1)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LaserControlClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaserControlClass::SignalTurnLaser2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LaserControlClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LaserControlClass::SignalTurnLaser3)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LaserControlClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_LaserControlClass.data,
    qt_meta_data_LaserControlClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LaserControlClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaserControlClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LaserControlClass.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LaserControlClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void LaserControlClass::SignalTurnLaser1(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LaserControlClass::SignalTurnLaser2(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LaserControlClass::SignalTurnLaser3(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
