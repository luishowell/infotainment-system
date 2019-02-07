/****************************************************************************
** Meta object code from reading C++ file 'Diagnostics.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/Diagnostics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Diagnostics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Diagnostics_t {
    QByteArrayData data[22];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Diagnostics_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Diagnostics_t qt_meta_stringdata_Diagnostics = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Diagnostics"
QT_MOC_LITERAL(1, 12, 13), // "DisplayChange"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7), // "state_t"
QT_MOC_LITERAL(4, 35, 9), // "req_state"
QT_MOC_LITERAL(5, 45, 8), // "QWidget*"
QT_MOC_LITERAL(6, 54, 11), // "currentView"
QT_MOC_LITERAL(7, 66, 17), // "NewChannelRequest"
QT_MOC_LITERAL(8, 84, 12), // "diagParams_t"
QT_MOC_LITERAL(9, 97, 13), // "dataRequested"
QT_MOC_LITERAL(10, 111, 13), // "obd2Channel_t"
QT_MOC_LITERAL(11, 125, 7), // "channel"
QT_MOC_LITERAL(12, 133, 12), // "StartLogging"
QT_MOC_LITERAL(13, 146, 19), // "StateChangeMainMenu"
QT_MOC_LITERAL(14, 166, 10), // "DiagDataRx"
QT_MOC_LITERAL(15, 177, 10), // "diagMsg_t*"
QT_MOC_LITERAL(16, 188, 3), // "msg"
QT_MOC_LITERAL(17, 192, 17), // "JourneyLogRequest"
QT_MOC_LITERAL(18, 210, 12), // "ShowRpmGauge"
QT_MOC_LITERAL(19, 223, 14), // "ShowSpeedGauge"
QT_MOC_LITERAL(20, 238, 16), // "ShowAirTempGauge"
QT_MOC_LITERAL(21, 255, 17) // "ShowThrottleGauge"

    },
    "Diagnostics\0DisplayChange\0\0state_t\0"
    "req_state\0QWidget*\0currentView\0"
    "NewChannelRequest\0diagParams_t\0"
    "dataRequested\0obd2Channel_t\0channel\0"
    "StartLogging\0StateChangeMainMenu\0"
    "DiagDataRx\0diagMsg_t*\0msg\0JourneyLogRequest\0"
    "ShowRpmGauge\0ShowSpeedGauge\0"
    "ShowAirTempGauge\0ShowThrottleGauge"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Diagnostics[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       7,    2,   69,    2, 0x06 /* Public */,
      12,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   75,    2, 0x0a /* Public */,
      14,    1,   76,    2, 0x0a /* Public */,
      17,    0,   79,    2, 0x0a /* Public */,
      18,    0,   80,    2, 0x0a /* Public */,
      19,    0,   81,    2, 0x0a /* Public */,
      20,    0,   82,    2, 0x0a /* Public */,
      21,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 10,    9,   11,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Diagnostics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Diagnostics *_t = static_cast<Diagnostics *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayChange((*reinterpret_cast< state_t(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: _t->NewChannelRequest((*reinterpret_cast< diagParams_t(*)>(_a[1])),(*reinterpret_cast< obd2Channel_t(*)>(_a[2]))); break;
        case 2: _t->StartLogging(); break;
        case 3: _t->StateChangeMainMenu(); break;
        case 4: _t->DiagDataRx((*reinterpret_cast< diagMsg_t*(*)>(_a[1]))); break;
        case 5: _t->JourneyLogRequest(); break;
        case 6: _t->ShowRpmGauge(); break;
        case 7: _t->ShowSpeedGauge(); break;
        case 8: _t->ShowAirTempGauge(); break;
        case 9: _t->ShowThrottleGauge(); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Diagnostics::*)(state_t , QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagnostics::DisplayChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Diagnostics::*)(diagParams_t , obd2Channel_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagnostics::NewChannelRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Diagnostics::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Diagnostics::StartLogging)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Diagnostics::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Diagnostics.data,
    qt_meta_data_Diagnostics,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Diagnostics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Diagnostics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Diagnostics.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Diagnostics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Diagnostics::DisplayChange(state_t _t1, QWidget * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Diagnostics::NewChannelRequest(diagParams_t _t1, obd2Channel_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Diagnostics::StartLogging()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
