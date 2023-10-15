/****************************************************************************
** Meta object code from reading C++ file 'SinusGeneratorClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SinusGeneratorClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SinusGeneratorClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SinusGeneratorClass_t {
    QByteArrayData data[16];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SinusGeneratorClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SinusGeneratorClass_t qt_meta_stringdata_SinusGeneratorClass = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SinusGeneratorClass"
QT_MOC_LITERAL(1, 20, 22), // "SignalNewDataAvailable"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "SetRelativeOutput"
QT_MOC_LITERAL(4, 62, 4), // "flag"
QT_MOC_LITERAL(5, 67, 16), // "SlotSetFrequency"
QT_MOC_LITERAL(6, 84, 4), // "Freq"
QT_MOC_LITERAL(7, 89, 16), // "SlotSetAmplitude"
QT_MOC_LITERAL(8, 106, 4), // "Ampl"
QT_MOC_LITERAL(9, 111, 21), // "SlotSetAmplitudeNoize"
QT_MOC_LITERAL(10, 133, 17), // "SlotEnableChannel"
QT_MOC_LITERAL(11, 151, 6), // "Enable"
QT_MOC_LITERAL(12, 158, 7), // "Channel"
QT_MOC_LITERAL(13, 166, 21), // "SlotCalculateNewValue"
QT_MOC_LITERAL(14, 188, 17), // "SlotStartGenerate"
QT_MOC_LITERAL(15, 206, 9) // "StartStop"

    },
    "SinusGeneratorClass\0SignalNewDataAvailable\0"
    "\0SetRelativeOutput\0flag\0SlotSetFrequency\0"
    "Freq\0SlotSetAmplitude\0Ampl\0"
    "SlotSetAmplitudeNoize\0SlotEnableChannel\0"
    "Enable\0Channel\0SlotCalculateNewValue\0"
    "SlotStartGenerate\0StartStop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SinusGeneratorClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   55,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    2,   67,    2, 0x0a /* Public */,
      13,    0,   72,    2, 0x0a /* Public */,
      14,    1,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void SinusGeneratorClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SinusGeneratorClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalNewDataAvailable(); break;
        case 1: _t->SetRelativeOutput((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->SlotSetFrequency((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->SlotSetAmplitude((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->SlotSetAmplitudeNoize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->SlotEnableChannel((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->SlotCalculateNewValue(); break;
        case 7: _t->SlotStartGenerate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SinusGeneratorClass::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SinusGeneratorClass::SignalNewDataAvailable)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SinusGeneratorClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SinusGeneratorClass.data,
    qt_meta_data_SinusGeneratorClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SinusGeneratorClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SinusGeneratorClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SinusGeneratorClass.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int SinusGeneratorClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SinusGeneratorClass::SignalNewDataAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
