/****************************************************************************
** Meta object code from reading C++ file 'StateManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/StateManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StateManager_t {
    QByteArrayData data[19];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StateManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StateManager_t qt_meta_stringdata_StateManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StateManager"
QT_MOC_LITERAL(1, 13, 13), // "DisplayChange"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 7), // "state_t"
QT_MOC_LITERAL(4, 36, 9), // "req_state"
QT_MOC_LITERAL(5, 46, 8), // "QWidget*"
QT_MOC_LITERAL(6, 55, 11), // "currentView"
QT_MOC_LITERAL(7, 67, 10), // "DiagDataTx"
QT_MOC_LITERAL(8, 78, 10), // "diagMsg_t*"
QT_MOC_LITERAL(9, 89, 3), // "msg"
QT_MOC_LITERAL(10, 93, 17), // "NewChannelRequest"
QT_MOC_LITERAL(11, 111, 12), // "diagParams_t"
QT_MOC_LITERAL(12, 124, 13), // "dataRequested"
QT_MOC_LITERAL(13, 138, 13), // "obd2Channel_t"
QT_MOC_LITERAL(14, 152, 7), // "channel"
QT_MOC_LITERAL(15, 160, 15), // "ChangeRequested"
QT_MOC_LITERAL(16, 176, 4), // "self"
QT_MOC_LITERAL(17, 181, 16), // "CANPublishDiagRx"
QT_MOC_LITERAL(18, 198, 19) // "OnNewChannelRequest"

    },
    "StateManager\0DisplayChange\0\0state_t\0"
    "req_state\0QWidget*\0currentView\0"
    "DiagDataTx\0diagMsg_t*\0msg\0NewChannelRequest\0"
    "diagParams_t\0dataRequested\0obd2Channel_t\0"
    "channel\0ChangeRequested\0self\0"
    "CANPublishDiagRx\0OnNewChannelRequest"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StateManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       7,    1,   49,    2, 0x06 /* Public */,
      10,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,   57,    2, 0x0a /* Public */,
      17,    1,   62,    2, 0x0a /* Public */,
      18,    2,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,   16,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 13,   12,   14,

       0        // eod
};

void StateManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StateManager *_t = static_cast<StateManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayChange((*reinterpret_cast< state_t(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: _t->DiagDataTx((*reinterpret_cast< diagMsg_t*(*)>(_a[1]))); break;
        case 2: _t->NewChannelRequest((*reinterpret_cast< diagParams_t(*)>(_a[1])),(*reinterpret_cast< obd2Channel_t(*)>(_a[2]))); break;
        case 3: _t->ChangeRequested((*reinterpret_cast< state_t(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 4: _t->CANPublishDiagRx((*reinterpret_cast< diagMsg_t*(*)>(_a[1]))); break;
        case 5: _t->OnNewChannelRequest((*reinterpret_cast< diagParams_t(*)>(_a[1])),(*reinterpret_cast< obd2Channel_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StateManager::*)(state_t , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StateManager::DisplayChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StateManager::*)(diagMsg_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StateManager::DiagDataTx)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StateManager::*)(diagParams_t , obd2Channel_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StateManager::NewChannelRequest)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StateManager::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_StateManager.data,
    qt_meta_data_StateManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StateManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StateManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StateManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int StateManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void StateManager::DisplayChange(state_t _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StateManager::DiagDataTx(diagMsg_t * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StateManager::NewChannelRequest(diagParams_t _t1, obd2Channel_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
