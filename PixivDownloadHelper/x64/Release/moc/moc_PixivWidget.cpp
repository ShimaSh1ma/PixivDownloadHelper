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
    QByteArrayData data[23];
    char stringdata0[359];
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
QT_MOC_LITERAL(4, 61, 19), // "refreshLayoutSignal"
QT_MOC_LITERAL(5, 81, 21), // "urlIsSingleWorkSignal"
QT_MOC_LITERAL(6, 103, 11), // "std::string"
QT_MOC_LITERAL(7, 115, 3), // "url"
QT_MOC_LITERAL(8, 119, 18), // "urlIsAllWorkSignal"
QT_MOC_LITERAL(9, 138, 2), // "id"
QT_MOC_LITERAL(10, 141, 21), // "urlIsTaggedWorkSignal"
QT_MOC_LITERAL(11, 163, 3), // "tag"
QT_MOC_LITERAL(12, 167, 15), // "addDownloadItem"
QT_MOC_LITERAL(13, 183, 8), // "checkUrl"
QT_MOC_LITERAL(14, 192, 21), // "getPixivAllIllustsUrl"
QT_MOC_LITERAL(15, 214, 24), // "getPixivTaggedIllustsUrl"
QT_MOC_LITERAL(16, 239, 13), // "startDownload"
QT_MOC_LITERAL(17, 253, 21), // "checkDownloadingOrNot"
QT_MOC_LITERAL(18, 275, 17), // "downloadCompleted"
QT_MOC_LITERAL(19, 293, 14), // "caculateColumn"
QT_MOC_LITERAL(20, 308, 12), // "adjustLayout"
QT_MOC_LITERAL(21, 321, 17), // "foldDownloadItems"
QT_MOC_LITERAL(22, 339, 19) // "unfoldDownloadItems"

    },
    "PixivDownloadItemWidget\0itemAddedSignal\0"
    "\0downloadStartSignal\0refreshLayoutSignal\0"
    "urlIsSingleWorkSignal\0std::string\0url\0"
    "urlIsAllWorkSignal\0id\0urlIsTaggedWorkSignal\0"
    "tag\0addDownloadItem\0checkUrl\0"
    "getPixivAllIllustsUrl\0getPixivTaggedIllustsUrl\0"
    "startDownload\0checkDownloadingOrNot\0"
    "downloadCompleted\0caculateColumn\0"
    "adjustLayout\0foldDownloadItems\0"
    "unfoldDownloadItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadItemWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    1,  102,    2, 0x06 /* Public */,
       8,    1,  105,    2, 0x06 /* Public */,
      10,    2,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,  113,    2, 0x0a /* Public */,
      13,    1,  116,    2, 0x0a /* Public */,
      14,    1,  119,    2, 0x0a /* Public */,
      15,    2,  122,    2, 0x0a /* Public */,
      16,    0,  127,    2, 0x0a /* Public */,
      17,    0,  128,    2, 0x0a /* Public */,
      18,    0,  129,    2, 0x0a /* Public */,
      19,    0,  130,    2, 0x0a /* Public */,
      20,    0,  131,    2, 0x0a /* Public */,
      21,    0,  132,    2, 0x0a /* Public */,
      22,    0,  133,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    9,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    9,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    9,   11,
    QMetaType::Void,
    QMetaType::Void,
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
        case 2: _t->refreshLayoutSignal(); break;
        case 3: _t->urlIsSingleWorkSignal((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->urlIsAllWorkSignal((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->urlIsTaggedWorkSignal((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 6: _t->addDownloadItem((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 7: _t->checkUrl((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 8: _t->getPixivAllIllustsUrl((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 9: _t->getPixivTaggedIllustsUrl((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 10: _t->startDownload(); break;
        case 11: _t->checkDownloadingOrNot(); break;
        case 12: _t->downloadCompleted(); break;
        case 13: _t->caculateColumn(); break;
        case 14: _t->adjustLayout(); break;
        case 15: _t->foldDownloadItems(); break;
        case 16: _t->unfoldDownloadItems(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::refreshLayoutSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsSingleWorkSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsAllWorkSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PixivDownloadItemWidget::*)(std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadItemWidget::urlIsTaggedWorkSignal)) {
                *result = 5;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
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
void PixivDownloadItemWidget::refreshLayoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PixivDownloadItemWidget::urlIsSingleWorkSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PixivDownloadItemWidget::urlIsAllWorkSignal(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PixivDownloadItemWidget::urlIsTaggedWorkSignal(std::string _t1, std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_PixivDownloadWidget_t {
    QByteArrayData data[3];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PixivDownloadWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PixivDownloadWidget_t qt_meta_stringdata_PixivDownloadWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PixivDownloadWidget"
QT_MOC_LITERAL(1, 20, 17), // "sizeChangedSignal"
QT_MOC_LITERAL(2, 38, 0) // ""

    },
    "PixivDownloadWidget\0sizeChangedSignal\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixivDownloadWidget[] = {

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
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void PixivDownloadWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PixivDownloadWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sizeChangedSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PixivDownloadWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PixivDownloadWidget::sizeChangedSignal)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PixivDownloadWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TransparentWidget::staticMetaObject>(),
    qt_meta_stringdata_PixivDownloadWidget.data,
    qt_meta_data_PixivDownloadWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PixivDownloadWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixivDownloadWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PixivDownloadWidget.stringdata0))
        return static_cast<void*>(this);
    return TransparentWidget::qt_metacast(_clname);
}

int PixivDownloadWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void PixivDownloadWidget::sizeChangedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
