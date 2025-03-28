/****************************************************************************
** Meta object code from reading C++ file 'glcanvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../glcanvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glcanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLCanvas_t {
    QByteArrayData data[10];
    char stringdata[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLCanvas_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLCanvas_t qt_meta_stringdata_GLCanvas = {
    {
QT_MOC_LITERAL(0, 0, 8), // "GLCanvas"
QT_MOC_LITERAL(1, 9, 15), // "mousePressEvent"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "QMouseEvent*"
QT_MOC_LITERAL(4, 39, 5), // "event"
QT_MOC_LITERAL(5, 45, 14), // "mouseMoveEvent"
QT_MOC_LITERAL(6, 60, 17), // "mouseReleaseEvent"
QT_MOC_LITERAL(7, 78, 13), // "keyPressEvent"
QT_MOC_LITERAL(8, 92, 10), // "QKeyEvent*"
QT_MOC_LITERAL(9, 103, 15) // "keyReleaseEvent"

    },
    "GLCanvas\0mousePressEvent\0\0QMouseEvent*\0"
    "event\0mouseMoveEvent\0mouseReleaseEvent\0"
    "keyPressEvent\0QKeyEvent*\0keyReleaseEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLCanvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, 0x80000000 | 8,    4,

       0        // eod
};

void GLCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLCanvas *_t = static_cast<GLCanvas *>(_o);
        switch (_id) {
        case 0: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 1: _t->mouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 3: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GLCanvas::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLCanvas.data,
      qt_meta_data_GLCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GLCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GLCanvas.stringdata))
        return static_cast<void*>(const_cast< GLCanvas*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
