/****************************************************************************
** Meta object code from reading C++ file 'CANThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/CANThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CANThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CANThread_t {
    QByteArrayData data[13];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CANThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CANThread_t qt_meta_stringdata_CANThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CANThread"
QT_MOC_LITERAL(1, 10, 16), // "CANPublishDiagTx"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "diagMsg_t*"
QT_MOC_LITERAL(4, 39, 3), // "msg"
QT_MOC_LITERAL(5, 43, 15), // "CANPublishLogTx"
QT_MOC_LITERAL(6, 59, 15), // "PublishDiagData"
QT_MOC_LITERAL(7, 75, 14), // "PublishLogData"
QT_MOC_LITERAL(8, 90, 19), // "OnNewChannelRequest"
QT_MOC_LITERAL(9, 110, 12), // "diagParams_t"
QT_MOC_LITERAL(10, 123, 13), // "dataRequested"
QT_MOC_LITERAL(11, 137, 13), // "obd2Channel_t"
QT_MOC_LITERAL(12, 151, 7) // "channel"

    },
    "CANThread\0CANPublishDiagTx\0\0diagMsg_t*\0"
    "msg\0CANPublishLogTx\0PublishDiagData\0"
    "PublishLogData\0OnNewChannelRequest\0"
    "diagParams_t\0dataRequested\0obd2Channel_t\0"
    "channel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CANThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x08 /* Private */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    2,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,

       0        // eod
};

void CANThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CANThread *_t = static_cast<CANThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CANPublishDiagTx((*reinterpret_cast< diagMsg_t*(*)>(_a[1]))); break;
        case 1: _t->CANPublishLogTx(); break;
        case 2: _t->PublishDiagData(); break;
        case 3: _t->PublishLogData(); break;
        case 4: _t->OnNewChannelRequest((*reinterpret_cast< diagParams_t(*)>(_a[1])),(*reinterpret_cast< obd2Channel_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CANThread::*)(diagMsg_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CANThread::CANPublishDiagTx)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CANThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CANThread::CANPublishLogTx)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CANThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_CANThread.data,
    qt_meta_data_CANThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CANThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CANThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CANThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int CANThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void CANThread::CANPublishDiagTx(diagMsg_t * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CANThread::CANPublishLogTx()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
