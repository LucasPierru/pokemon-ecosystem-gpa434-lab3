/****************************************************************************
** Meta object code from reading C++ file 'GPA434_Lab3_pro.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../GPA434_Lab3_pro.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GPA434_Lab3_pro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPA434_Lab3_pro_t {
    QByteArrayData data[8];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPA434_Lab3_pro_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPA434_Lab3_pro_t qt_meta_stringdata_GPA434_Lab3_pro = {
    {
QT_MOC_LITERAL(0, 0, 15), // "GPA434_Lab3_pro"
QT_MOC_LITERAL(1, 16, 15), // "startSimulation"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 14), // "stepSimulation"
QT_MOC_LITERAL(4, 48, 15), // "pauseSimulation"
QT_MOC_LITERAL(5, 64, 16), // "resumeSimulation"
QT_MOC_LITERAL(6, 81, 14), // "stopSimulation"
QT_MOC_LITERAL(7, 96, 5) // "about"

    },
    "GPA434_Lab3_pro\0startSimulation\0\0"
    "stepSimulation\0pauseSimulation\0"
    "resumeSimulation\0stopSimulation\0about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPA434_Lab3_pro[] = {

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

void GPA434_Lab3_pro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPA434_Lab3_pro *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startSimulation(); break;
        case 1: _t->stepSimulation(); break;
        case 2: _t->pauseSimulation(); break;
        case 3: _t->resumeSimulation(); break;
        case 4: _t->stopSimulation(); break;
        case 5: _t->about(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GPA434_Lab3_pro::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_GPA434_Lab3_pro.data,
    qt_meta_data_GPA434_Lab3_pro,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPA434_Lab3_pro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPA434_Lab3_pro::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPA434_Lab3_pro.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int GPA434_Lab3_pro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
