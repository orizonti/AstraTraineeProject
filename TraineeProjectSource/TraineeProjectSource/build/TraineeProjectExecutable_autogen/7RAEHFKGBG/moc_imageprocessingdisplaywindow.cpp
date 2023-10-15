/****************************************************************************
** Meta object code from reading C++ file 'imageprocessingdisplaywindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../gui_sources/imageprocessingdisplaywindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageprocessingdisplaywindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageProcessingDisplayWindow_t {
    QByteArrayData data[7];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcessingDisplayWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcessingDisplayWindow_t qt_meta_stringdata_ImageProcessingDisplayWindow = {
    {
QT_MOC_LITERAL(0, 0, 28), // "ImageProcessingDisplayWindow"
QT_MOC_LITERAL(1, 29, 19), // "SignalDisplayROIPos"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 30), // "QVector<QPair<double,double> >"
QT_MOC_LITERAL(4, 81, 6), // "Coords"
QT_MOC_LITERAL(5, 88, 9), // "CoordsROI"
QT_MOC_LITERAL(6, 98, 13) // "DisplayROIPos"

    },
    "ImageProcessingDisplayWindow\0"
    "SignalDisplayROIPos\0\0"
    "QVector<QPair<double,double> >\0Coords\0"
    "CoordsROI\0DisplayROIPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcessingDisplayWindow[] = {

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
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,

       0        // eod
};

void ImageProcessingDisplayWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageProcessingDisplayWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SignalDisplayROIPos((*reinterpret_cast< QVector<QPair<double,double> >(*)>(_a[1])),(*reinterpret_cast< QVector<QPair<double,double> >(*)>(_a[2]))); break;
        case 1: _t->DisplayROIPos((*reinterpret_cast< QVector<QPair<double,double> >(*)>(_a[1])),(*reinterpret_cast< QVector<QPair<double,double> >(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageProcessingDisplayWindow::*)(QVector<QPair<double,double> > , QVector<QPair<double,double> > );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageProcessingDisplayWindow::SignalDisplayROIPos)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageProcessingDisplayWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<AdjustableWidget::staticMetaObject>(),
    qt_meta_stringdata_ImageProcessingDisplayWindow.data,
    qt_meta_data_ImageProcessingDisplayWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageProcessingDisplayWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcessingDisplayWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcessingDisplayWindow.stringdata0))
        return static_cast<void*>(this);
    return AdjustableWidget::qt_metacast(_clname);
}

int ImageProcessingDisplayWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AdjustableWidget::qt_metacall(_c, _id, _a);
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
void ImageProcessingDisplayWindow::SignalDisplayROIPos(QVector<QPair<double,double> > _t1, QVector<QPair<double,double> > _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
