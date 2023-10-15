/****************************************************************************
** Meta object code from reading C++ file 'LaserPointerInterfaceClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../LaserPointerInterfaceClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LaserPointerInterfaceClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LaserPointerInterfaceClass_t {
    QByteArrayData data[11];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LaserPointerInterfaceClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LaserPointerInterfaceClass_t qt_meta_stringdata_LaserPointerInterfaceClass = {
    {
QT_MOC_LITERAL(0, 0, 26), // "LaserPointerInterfaceClass"
QT_MOC_LITERAL(1, 27, 12), // "SlotReadData"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "TurnOnOff675nm"
QT_MOC_LITERAL(4, 56, 14), // "TurnOnOff975nm"
QT_MOC_LITERAL(5, 71, 15), // "TurnOnOff1064nm"
QT_MOC_LITERAL(6, 87, 11), // "SetPower675"
QT_MOC_LITERAL(7, 99, 11), // "SetPower975"
QT_MOC_LITERAL(8, 111, 12), // "SetPower1065"
QT_MOC_LITERAL(9, 124, 13), // "ConnectToPort"
QT_MOC_LITERAL(10, 138, 8) // "PortName"

    },
    "LaserPointerInterfaceClass\0SlotReadData\0"
    "\0TurnOnOff675nm\0TurnOnOff975nm\0"
    "TurnOnOff1064nm\0SetPower675\0SetPower975\0"
    "SetPower1065\0ConnectToPort\0PortName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LaserPointerInterfaceClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void LaserPointerInterfaceClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LaserPointerInterfaceClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SlotReadData(); break;
        case 1: _t->TurnOnOff675nm(); break;
        case 2: _t->TurnOnOff975nm(); break;
        case 3: _t->TurnOnOff1064nm(); break;
        case 4: _t->SetPower675(); break;
        case 5: _t->SetPower975(); break;
        case 6: _t->SetPower1065(); break;
        case 7: _t->ConnectToPort((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LaserPointerInterfaceClass::staticMetaObject = { {
    QMetaObject::SuperData::link<CommonLaserInterfaceClass::staticMetaObject>(),
    qt_meta_stringdata_LaserPointerInterfaceClass.data,
    qt_meta_data_LaserPointerInterfaceClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LaserPointerInterfaceClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LaserPointerInterfaceClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LaserPointerInterfaceClass.stringdata0))
        return static_cast<void*>(this);
    return CommonLaserInterfaceClass::qt_metacast(_clname);
}

int LaserPointerInterfaceClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CommonLaserInterfaceClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
