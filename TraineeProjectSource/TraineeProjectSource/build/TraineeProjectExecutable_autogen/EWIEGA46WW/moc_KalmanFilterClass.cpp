/****************************************************************************
** Meta object code from reading C++ file 'KalmanFilterClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../KalmanFilterClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KalmanFilterClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SinusFilter_t {
    QByteArrayData data[6];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SinusFilter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SinusFilter_t qt_meta_stringdata_SinusFilter = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SinusFilter"
QT_MOC_LITERAL(1, 12, 17), // "SignalOutputCoord"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "QPair<double,double>"
QT_MOC_LITERAL(4, 52, 12), // "SlotSetCoord"
QT_MOC_LITERAL(5, 65, 5) // "Coord"

    },
    "SinusFilter\0SignalOutputCoord\0\0"
    "QPair<double,double>\0SlotSetCoord\0"
    "Coord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SinusFilter[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    5,

       0        // eod
};

void SinusFilter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SinusFilter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalOutputCoord((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        case 1: _t->SlotSetCoord((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SinusFilter::*)(QPair<double,double> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SinusFilter::SignalOutputCoord)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SinusFilter::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SinusFilter.data,
    qt_meta_data_SinusFilter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SinusFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SinusFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SinusFilter.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int SinusFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SinusFilter::SignalOutputCoord(QPair<double,double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Derivative_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Derivative_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Derivative_t qt_meta_stringdata_Derivative = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Derivative"
QT_MOC_LITERAL(1, 11, 18), // "SendCoordToPerform"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "QPair<double,double>"
QT_MOC_LITERAL(4, 52, 18), // "SlotGetOutputCoord"
QT_MOC_LITERAL(5, 71, 5) // "Coord"

    },
    "Derivative\0SendCoordToPerform\0\0"
    "QPair<double,double>\0SlotGetOutputCoord\0"
    "Coord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Derivative[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    5,

       0        // eod
};

void Derivative::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Derivative *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendCoordToPerform((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        case 1: _t->SlotGetOutputCoord((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Derivative::*)(QPair<double,double> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Derivative::SendCoordToPerform)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Derivative::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Derivative.data,
    qt_meta_data_Derivative,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Derivative::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Derivative::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Derivative.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int Derivative::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Derivative::SendCoordToPerform(QPair<double,double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_KalmanFilterClass_t {
    QByteArrayData data[5];
    char stringdata0[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KalmanFilterClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KalmanFilterClass_t qt_meta_stringdata_KalmanFilterClass = {
    {
QT_MOC_LITERAL(0, 0, 17), // "KalmanFilterClass"
QT_MOC_LITERAL(1, 18, 18), // "SendCoordToPerform"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "QPair<double,double>"
QT_MOC_LITERAL(4, 59, 5) // "Coord"

    },
    "KalmanFilterClass\0SendCoordToPerform\0"
    "\0QPair<double,double>\0Coord"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KalmanFilterClass[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void KalmanFilterClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KalmanFilterClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendCoordToPerform((*reinterpret_cast< QPair<double,double>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KalmanFilterClass::*)(QPair<double,double> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KalmanFilterClass::SendCoordToPerform)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KalmanFilterClass::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_KalmanFilterClass.data,
    qt_meta_data_KalmanFilterClass,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KalmanFilterClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KalmanFilterClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KalmanFilterClass.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "PassTwoCoordClass"))
        return static_cast< PassTwoCoordClass*>(this);
    return QObject::qt_metacast(_clname);
}

int KalmanFilterClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void KalmanFilterClass::SendCoordToPerform(QPair<double,double> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
