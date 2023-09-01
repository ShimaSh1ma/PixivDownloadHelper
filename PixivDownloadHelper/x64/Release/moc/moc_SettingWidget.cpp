/****************************************************************************
** Meta object code from reading C++ file 'SettingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../SettingWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SettingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChangeDownloadPathWidget_t {
    QByteArrayData data[3];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChangeDownloadPathWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChangeDownloadPathWidget_t qt_meta_stringdata_ChangeDownloadPathWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ChangeDownloadPathWidget"
QT_MOC_LITERAL(1, 25, 18), // "chooseDownloadPath"
QT_MOC_LITERAL(2, 44, 0) // ""

    },
    "ChangeDownloadPathWidget\0chooseDownloadPath\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChangeDownloadPathWidget[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ChangeDownloadPathWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChangeDownloadPathWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->chooseDownloadPath(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ChangeDownloadPathWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TranslucentWidget::staticMetaObject>(),
    qt_meta_stringdata_ChangeDownloadPathWidget.data,
    qt_meta_data_ChangeDownloadPathWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChangeDownloadPathWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChangeDownloadPathWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeDownloadPathWidget.stringdata0))
        return static_cast<void*>(this);
    return TranslucentWidget::qt_metacast(_clname);
}

int ChangeDownloadPathWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TranslucentWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ChangePixivCookieWidget_t {
    QByteArrayData data[4];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChangePixivCookieWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChangePixivCookieWidget_t qt_meta_stringdata_ChangePixivCookieWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ChangePixivCookieWidget"
QT_MOC_LITERAL(1, 24, 10), // "saveCookie"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12) // "turnEditable"

    },
    "ChangePixivCookieWidget\0saveCookie\0\0"
    "turnEditable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChangePixivCookieWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChangePixivCookieWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChangePixivCookieWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveCookie(); break;
        case 1: _t->turnEditable(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ChangePixivCookieWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TranslucentWidget::staticMetaObject>(),
    qt_meta_stringdata_ChangePixivCookieWidget.data,
    qt_meta_data_ChangePixivCookieWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChangePixivCookieWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChangePixivCookieWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChangePixivCookieWidget.stringdata0))
        return static_cast<void*>(this);
    return TranslucentWidget::qt_metacast(_clname);
}

int ChangePixivCookieWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TranslucentWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ChangeTransparencyWidget_t {
    QByteArrayData data[3];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChangeTransparencyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChangeTransparencyWidget_t qt_meta_stringdata_ChangeTransparencyWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ChangeTransparencyWidget"
QT_MOC_LITERAL(1, 25, 15), // "saveTranparency"
QT_MOC_LITERAL(2, 41, 0) // ""

    },
    "ChangeTransparencyWidget\0saveTranparency\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChangeTransparencyWidget[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ChangeTransparencyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChangeTransparencyWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->saveTranparency(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ChangeTransparencyWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TranslucentWidget::staticMetaObject>(),
    qt_meta_stringdata_ChangeTransparencyWidget.data,
    qt_meta_data_ChangeTransparencyWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChangeTransparencyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChangeTransparencyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeTransparencyWidget.stringdata0))
        return static_cast<void*>(this);
    return TranslucentWidget::qt_metacast(_clname);
}

int ChangeTransparencyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TranslucentWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ChangeBackgroundImageWidget_t {
    QByteArrayData data[4];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChangeBackgroundImageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChangeBackgroundImageWidget_t qt_meta_stringdata_ChangeBackgroundImageWidget = {
    {
QT_MOC_LITERAL(0, 0, 27), // "ChangeBackgroundImageWidget"
QT_MOC_LITERAL(1, 28, 17), // "backgroundChanged"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 11) // "chooseImage"

    },
    "ChangeBackgroundImageWidget\0"
    "backgroundChanged\0\0chooseImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChangeBackgroundImageWidget[] = {

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

void ChangeBackgroundImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChangeBackgroundImageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backgroundChanged(); break;
        case 1: _t->chooseImage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChangeBackgroundImageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChangeBackgroundImageWidget::backgroundChanged)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ChangeBackgroundImageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TranslucentWidget::staticMetaObject>(),
    qt_meta_stringdata_ChangeBackgroundImageWidget.data,
    qt_meta_data_ChangeBackgroundImageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChangeBackgroundImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChangeBackgroundImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChangeBackgroundImageWidget.stringdata0))
        return static_cast<void*>(this);
    return TranslucentWidget::qt_metacast(_clname);
}

int ChangeBackgroundImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TranslucentWidget::qt_metacall(_c, _id, _a);
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
void ChangeBackgroundImageWidget::backgroundChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
