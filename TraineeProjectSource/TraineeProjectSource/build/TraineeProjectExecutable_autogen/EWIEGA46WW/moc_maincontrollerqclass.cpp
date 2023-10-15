/****************************************************************************
** Meta object code from reading C++ file 'maincontrollerqclass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../maincontrollerqclass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maincontrollerqclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestSignals_t {
    QByteArrayData data[4];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestSignals_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestSignals_t qt_meta_stringdata_TestSignals = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TestSignals"
QT_MOC_LITERAL(1, 12, 22), // "SignalNewDataAvailable"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 15) // "GenerateNewData"

    },
    "TestSignals\0SignalNewDataAvailable\0\0"
    "GenerateNewData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestSignals[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TestSignals::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestSignals *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalNewDataAvailable(); break;
        case 1: _t->GenerateNewData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TestSignals::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TestSignals::SignalNewDataAvailable)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TestSignals::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TestSignals.data,
    qt_meta_data_TestSignals,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestSignals::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestSignals::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestSignals.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int TestSignals::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TestSignals::SignalNewDataAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_MainControllerQClass_t {
    QByteArrayData data[24];
    char stringdata0[446];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainControllerQClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainControllerQClass_t qt_meta_stringdata_MainControllerQClass = {
    {
QT_MOC_LITERAL(0, 0, 20), // "MainControllerQClass"
QT_MOC_LITERAL(1, 21, 19), // "SignalImageReceived"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 24), // "SignalStartIterateLasers"
QT_MOC_LITERAL(4, 67, 21), // "SignalSwitchAllLasers"
QT_MOC_LITERAL(5, 89, 12), // "WorkFinished"
QT_MOC_LITERAL(6, 102, 32), // "SlotFindSpot_MoveEngineToWorkPos"
QT_MOC_LITERAL(7, 135, 16), // "SlotReceiveImage"
QT_MOC_LITERAL(8, 152, 28), // "SlotReceiveErrorRemoteSensor"
QT_MOC_LITERAL(9, 181, 34), // "SlotCheckDisplayDeviceModules..."
QT_MOC_LITERAL(10, 216, 26), // "SlotInnerRotateCalibration"
QT_MOC_LITERAL(11, 243, 19), // "SlotReciveErrorTest"
QT_MOC_LITERAL(12, 263, 18), // "SlotSetAimingCoord"
QT_MOC_LITERAL(13, 282, 1), // "x"
QT_MOC_LITERAL(14, 284, 1), // "y"
QT_MOC_LITERAL(15, 286, 13), // "NumberChannel"
QT_MOC_LITERAL(16, 300, 17), // "SlotStartStopWork"
QT_MOC_LITERAL(17, 318, 9), // "StartStop"
QT_MOC_LITERAL(18, 328, 16), // "SlotMoveByCircle"
QT_MOC_LITERAL(19, 345, 21), // "SlotStartMoveByCircle"
QT_MOC_LITERAL(20, 367, 5), // "OnOff"
QT_MOC_LITERAL(21, 373, 26), // "SetAdjustModeWithCrossHair"
QT_MOC_LITERAL(22, 400, 30), // "StartSystemRotationCalibration"
QT_MOC_LITERAL(23, 431, 14) // "SlotFinishWork"

    },
    "MainControllerQClass\0SignalImageReceived\0"
    "\0SignalStartIterateLasers\0"
    "SignalSwitchAllLasers\0WorkFinished\0"
    "SlotFindSpot_MoveEngineToWorkPos\0"
    "SlotReceiveImage\0SlotReceiveErrorRemoteSensor\0"
    "SlotCheckDisplayDeviceModulesState\0"
    "SlotInnerRotateCalibration\0"
    "SlotReciveErrorTest\0SlotSetAimingCoord\0"
    "x\0y\0NumberChannel\0SlotStartStopWork\0"
    "StartStop\0SlotMoveByCircle\0"
    "SlotStartMoveByCircle\0OnOff\0"
    "SetAdjustModeWithCrossHair\0"
    "StartSystemRotationCalibration\0"
    "SlotFinishWork"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainControllerQClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    1,  100,    2, 0x06 /* Public */,
       4,    1,  103,    2, 0x06 /* Public */,
       5,    0,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  107,    2, 0x0a /* Public */,
       7,    0,  108,    2, 0x0a /* Public */,
       8,    0,  109,    2, 0x0a /* Public */,
       9,    0,  110,    2, 0x0a /* Public */,
      10,    0,  111,    2, 0x0a /* Public */,
      11,    0,  112,    2, 0x0a /* Public */,
      12,    3,  113,    2, 0x0a /* Public */,
      16,    1,  120,    2, 0x0a /* Public */,
      18,    0,  123,    2, 0x0a /* Public */,
      19,    1,  124,    2, 0x0a /* Public */,
      21,    1,  127,    2, 0x0a /* Public */,
      22,    0,  130,    2, 0x0a /* Public */,
      23,    0,  131,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainControllerQClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainControllerQClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalImageReceived(); break;
        case 1: _t->SignalStartIterateLasers((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->SignalSwitchAllLasers((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->WorkFinished(); break;
        case 4: _t->SlotFindSpot_MoveEngineToWorkPos(); break;
        case 5: _t->SlotReceiveImage(); break;
        case 6: _t->SlotReceiveErrorRemoteSensor(); break;
        case 7: _t->SlotCheckDisplayDeviceModulesState(); break;
        case 8: _t->SlotInnerRotateCalibration(); break;
        case 9: _t->SlotReciveErrorTest(); break;
        case 10: _t->SlotSetAimingCoord((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->SlotStartStopWork((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->SlotMoveByCircle(); break;
        case 13: _t->SlotStartMoveByCircle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->SetAdjustModeWithCrossHair((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->StartSystemRotationCalibration(); break;
        case 16: _t->SlotFinishWork(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainControllerQClass::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainControllerQClass::SignalImageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainControllerQClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainControllerQClass::SignalStartIterateLasers)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainControllerQClass::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainControllerQClass::SignalSwitchAllLasers)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainControllerQClass::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainControllerQClass::WorkFinished)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainControllerQClass::staticMetaObject = { {
    QMetaObject::SuperData::link<HandleControlInterface::staticMetaObject>(),
    qt_meta_stringdata_MainControllerQClass.data,
    qt_meta_data_MainControllerQClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainControllerQClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainControllerQClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainControllerQClass.stringdata0))
        return static_cast<void*>(this);
    return HandleControlInterface::qt_metacast(_clname);
}

int MainControllerQClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = HandleControlInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void MainControllerQClass::SignalImageReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainControllerQClass::SignalStartIterateLasers(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainControllerQClass::SignalSwitchAllLasers(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainControllerQClass::WorkFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
