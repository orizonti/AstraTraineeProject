/****************************************************************************
** Meta object code from reading C++ file 'graphicswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui_sources/graphicswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsInterface_t {
    QByteArrayData data[5];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsInterface_t qt_meta_stringdata_GraphicsInterface = {
    {
QT_MOC_LITERAL(0, 0, 17), // "GraphicsInterface"
QT_MOC_LITERAL(1, 18, 12), // "DisplayGraph"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 25), // "DataAimingErrorStructure&"
QT_MOC_LITERAL(4, 58, 4) // "Data"

    },
    "GraphicsInterface\0DisplayGraph\0\0"
    "DataAimingErrorStructure&\0Data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GraphicsInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicsInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayGraph((*reinterpret_cast< DataAimingErrorStructure(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicsInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GraphicsInterface.data,
    qt_meta_data_GraphicsInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GraphicsInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_GraphicsWindow_t {
    QByteArrayData data[10];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsWindow_t qt_meta_stringdata_GraphicsWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "GraphicsWindow"
QT_MOC_LITERAL(1, 15, 13), // "SignalNewData"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 24), // "DataAimingErrorStructure"
QT_MOC_LITERAL(4, 55, 4), // "Data"
QT_MOC_LITERAL(5, 60, 17), // "DisplayAimingData"
QT_MOC_LITERAL(6, 78, 15), // "ChangeDataLimit"
QT_MOC_LITERAL(7, 94, 7), // "Channel"
QT_MOC_LITERAL(8, 102, 11), // "DataLimitup"
QT_MOC_LITERAL(9, 114, 13) // "DataLimitDown"

    },
    "GraphicsWindow\0SignalNewData\0\0"
    "DataAimingErrorStructure\0Data\0"
    "DisplayAimingData\0ChangeDataLimit\0"
    "Channel\0DataLimitup\0DataLimitDown"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x0a /* Public */,
       6,    3,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    7,    8,    9,

       0        // eod
};

void GraphicsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GraphicsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalNewData((*reinterpret_cast< DataAimingErrorStructure(*)>(_a[1]))); break;
        case 1: _t->DisplayAimingData((*reinterpret_cast< DataAimingErrorStructure(*)>(_a[1]))); break;
        case 2: _t->ChangeDataLimit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GraphicsWindow::*)(DataAimingErrorStructure );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GraphicsWindow::SignalNewData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GraphicsWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<AdjustableWidget::staticMetaObject>(),
    qt_meta_stringdata_GraphicsWindow.data,
    qt_meta_data_GraphicsWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsWindow.stringdata0))
        return static_cast<void*>(this);
    return AdjustableWidget::qt_metacast(_clname);
}

int GraphicsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AdjustableWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GraphicsWindow::SignalNewData(DataAimingErrorStructure _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
