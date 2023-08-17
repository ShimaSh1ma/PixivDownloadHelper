/****************************************************************************
** Meta object code from reading C++ file 'PixivWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../PixivWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PixivWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PixivDownloadItemPreviewWidget_t {
    QByteArrayData data[5];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixivDownloadItemPreviewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixivDownloadItemPreviewWidget_t qt_meta_stringdata_PixivDownloadItemPreviewWidget = {
    {
QT_MOC_LITERAL(0, 0, 30), // "PixivDownloadItemPreviewWidget"
QT_MOC_LITERAL(1, 31, 16), // "loadPreviewImage"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 11), // "std::string"
QT_MOC_LITERAL(4, 61, 9) // "imagePath"

    },
    "PixivDownloadItemPreviewWidget\0"
    "loadPreviewImage\0\0std::string\0imagePath"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadItemPreviewWidget[] = {

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

void PixivDownloadItemPreviewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixivDownloadItemPreviewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadPreviewImage((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PixivDownloadItemPreviewWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TransparentWidget::staticMetaObject>(),
    qt_meta_stringdata_PixivDownloadItemPreviewWidget.data,
    qt_meta_data_PixivDownloadItemPreviewWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixivDownloadItemPreviewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixivDownloadItemPreviewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixivDownloadItemPreviewWidget.stringdata0))
        return static_cast<void*>(this);
    return TransparentWidget::qt_metacast(_clname);
}

int PixivDownloadItemPreviewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TransparentWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_PixivDownloadItemStateWidget_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixivDownloadItemStateWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixivDownloadItemStateWidget_t qt_meta_stringdata_PixivDownloadItemStateWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "PixivDownloadItemStateWidget"
QT_MOC_LITERAL(1, 29, 8), // "setState"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 13), // "downloadState"
QT_MOC_LITERAL(4, 53, 6), // "_state"
QT_MOC_LITERAL(5, 60, 11), // "setProgress"
QT_MOC_LITERAL(6, 72, 5), // "total"
QT_MOC_LITERAL(7, 78, 7) // "success"

    },
    "PixivDownloadItemStateWidget\0setState\0"
    "\0downloadState\0_state\0setProgress\0"
    "total\0success"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadItemStateWidget[] = {

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
       1,    1,   24,    2, 0x0a /* Public */,
       5,    2,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

       0        // eod
};

void PixivDownloadItemStateWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixivDownloadItemStateWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setState((*reinterpret_cast< const downloadState(*)>(_a[1]))); break;
        case 1: _t->setProgress((*reinterpret_cast< const int(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PixivDownloadItemStateWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TransparentWidget::staticMetaObject>(),
    qt_meta_stringdata_PixivDownloadItemStateWidget.data,
    qt_meta_data_PixivDownloadItemStateWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixivDownloadItemStateWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixivDownloadItemStateWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixivDownloadItemStateWidget.stringdata0))
        return static_cast<void*>(this);
    return TransparentWidget::qt_metacast(_clname);
}

int PixivDownloadItemStateWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TransparentWidget::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_PixivDownloadItem_t {
    QByteArrayData data[9];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixivDownloadItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixivDownloadItem_t qt_meta_stringdata_PixivDownloadItem = {
    {
QT_MOC_LITERAL(0, 0, 17), // "PixivDownloadItem"
QT_MOC_LITERAL(1, 18, 18), // "previewImageSignal"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 11), // "std::string"
QT_MOC_LITERAL(4, 50, 22), // "downloadCompleteSignal"
QT_MOC_LITERAL(5, 73, 22), // "downloadProgressSignal"
QT_MOC_LITERAL(6, 96, 5), // "total"
QT_MOC_LITERAL(7, 102, 7), // "success"
QT_MOC_LITERAL(8, 110, 13) // "pixivDownload"

    },
    "PixivDownloadItem\0previewImageSignal\0"
    "\0std::string\0downloadCompleteSignal\0"
    "downloadProgressSignal\0total\0success\0"
    "pixivDownload"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,
       5,    2,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PixivDownloadItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixivDownloadItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->previewImageSignal((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->downloadCompleteSignal(); break;
        case 2: _t->downloadProgressSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->pixivDownload(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PixivDownloadItem::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItem::previewImageSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItem::downloadCompleteSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItem::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItem::downloadProgressSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PixivDownloadItem::staticMetaObject = { {
    QMetaObject::SuperData::link<TranslucentWidget::staticMetaObject>(),
    qt_meta_stringdata_PixivDownloadItem.data,
    qt_meta_data_PixivDownloadItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixivDownloadItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixivDownloadItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixivDownloadItem.stringdata0))
        return static_cast<void*>(this);
    return TranslucentWidget::qt_metacast(_clname);
}

int PixivDownloadItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TranslucentWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PixivDownloadItem::previewImageSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PixivDownloadItem::downloadCompleteSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PixivDownloadItem::downloadProgressSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_PixivDownloadItemWidget_t {
    QByteArrayData data[22];
    char stringdata0[338];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixivDownloadItemWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixivDownloadItemWidget_t qt_meta_stringdata_PixivDownloadItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "PixivDownloadItemWidget"
QT_MOC_LITERAL(1, 24, 15), // "itemAddedSignal"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 19), // "downloadStartSignal"
QT_MOC_LITERAL(4, 61, 16), // "sizeChangeSignal"
QT_MOC_LITERAL(5, 78, 19), // "refreshLayoutSignal"
QT_MOC_LITERAL(6, 98, 21), // "urlIsSingleWorkSignal"
QT_MOC_LITERAL(7, 120, 11), // "std::string"
QT_MOC_LITERAL(8, 132, 3), // "url"
QT_MOC_LITERAL(9, 136, 18), // "urlIsAllWorkSignal"
QT_MOC_LITERAL(10, 155, 2), // "id"
QT_MOC_LITERAL(11, 158, 21), // "urlIsTaggedWorkSignal"
QT_MOC_LITERAL(12, 180, 3), // "tag"
QT_MOC_LITERAL(13, 184, 15), // "addDownloadItem"
QT_MOC_LITERAL(14, 200, 8), // "checkUrl"
QT_MOC_LITERAL(15, 209, 21), // "getPixivAllIllustsUrl"
QT_MOC_LITERAL(16, 231, 24), // "getPixivTaggedIllustsUrl"
QT_MOC_LITERAL(17, 256, 13), // "startDownload"
QT_MOC_LITERAL(18, 270, 21), // "checkDownloadingOrNot"
QT_MOC_LITERAL(19, 292, 17), // "downloadCompleted"
QT_MOC_LITERAL(20, 310, 14), // "caculateColumn"
QT_MOC_LITERAL(21, 325, 12) // "adjustLayout"

    },
    "PixivDownloadItemWidget\0itemAddedSignal\0"
    "\0downloadStartSignal\0sizeChangeSignal\0"
    "refreshLayoutSignal\0urlIsSingleWorkSignal\0"
    "std::string\0url\0urlIsAllWorkSignal\0"
    "id\0urlIsTaggedWorkSignal\0tag\0"
    "addDownloadItem\0checkUrl\0getPixivAllIllustsUrl\0"
    "getPixivTaggedIllustsUrl\0startDownload\0"
    "checkDownloadingOrNot\0downloadCompleted\0"
    "caculateColumn\0adjustLayout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadItemWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    1,   98,    2, 0x06 /* Public */,
       9,    1,  101,    2, 0x06 /* Public */,
      11,    2,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  109,    2, 0x0a /* Public */,
      14,    1,  112,    2, 0x0a /* Public */,
      15,    1,  115,    2, 0x0a /* Public */,
      16,    2,  118,    2, 0x0a /* Public */,
      17,    0,  123,    2, 0x0a /* Public */,
      18,    0,  124,    2, 0x0a /* Public */,
      19,    0,  125,    2, 0x0a /* Public */,
      20,    0,  126,    2, 0x0a /* Public */,
      21,    0,  127,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   10,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,   10,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   10,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,   10,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PixivDownloadItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixivDownloadItemWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemAddedSignal(); break;
        case 1: _t->downloadStartSignal(); break;
        case 2: _t->sizeChangeSignal(); break;
        case 3: _t->refreshLayoutSignal(); break;
        case 4: _t->urlIsSingleWorkSignal((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->urlIsAllWorkSignal((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->urlIsTaggedWorkSignal((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 7: _t->addDownloadItem((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 8: _t->checkUrl((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 9: _t->getPixivAllIllustsUrl((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 10: _t->getPixivTaggedIllustsUrl((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 11: _t->startDownload(); break;
        case 12: _t->checkDownloadingOrNot(); break;
        case 13: _t->downloadCompleted(); break;
        case 14: _t->caculateColumn(); break;
        case 15: _t->adjustLayout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PixivDownloadItemWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::itemAddedSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::downloadStartSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::sizeChangeSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::refreshLayoutSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsSingleWorkSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsAllWorkSignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsTaggedWorkSignal)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PixivDownloadItemWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TransparentWidget::staticMetaObject>(),
    qt_meta_stringdata_PixivDownloadItemWidget.data,
    qt_meta_data_PixivDownloadItemWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixivDownloadItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixivDownloadItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixivDownloadItemWidget.stringdata0))
        return static_cast<void*>(this);
    return TransparentWidget::qt_metacast(_clname);
}

int PixivDownloadItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TransparentWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void PixivDownloadItemWidget::itemAddedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PixivDownloadItemWidget::downloadStartSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PixivDownloadItemWidget::sizeChangeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PixivDownloadItemWidget::refreshLayoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PixivDownloadItemWidget::urlIsSingleWorkSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PixivDownloadItemWidget::urlIsAllWorkSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PixivDownloadItemWidget::urlIsTaggedWorkSignal(std::string _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
