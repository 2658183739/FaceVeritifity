/****************************************************************************
** Meta object code from reading C++ file 'faceverify.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../faceverify.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'faceverify.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FaceVerify_t {
    QByteArrayData data[23];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FaceVerify_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FaceVerify_t qt_meta_stringdata_FaceVerify = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FaceVerify"
QT_MOC_LITERAL(1, 11, 13), // "Veryfity_face"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "facenum"
QT_MOC_LITERAL(4, 34, 8), // "facename"
QT_MOC_LITERAL(5, 43, 9), // "Send_Card"
QT_MOC_LITERAL(6, 53, 8), // "SetImage"
QT_MOC_LITERAL(7, 62, 3), // "src"
QT_MOC_LITERAL(8, 66, 11), // "setCardData"
QT_MOC_LITERAL(9, 78, 3), // "str"
QT_MOC_LITERAL(10, 82, 9), // "Get_image"
QT_MOC_LITERAL(11, 92, 7), // "QImage*"
QT_MOC_LITERAL(12, 100, 5), // "image"
QT_MOC_LITERAL(13, 106, 27), // "on_pushButton_Train_clicked"
QT_MOC_LITERAL(14, 134, 12), // "Train_Finish"
QT_MOC_LITERAL(15, 147, 9), // "Show_Data"
QT_MOC_LITERAL(16, 157, 13), // "QSqlDatabase*"
QT_MOC_LITERAL(17, 171, 4), // "m_db"
QT_MOC_LITERAL(18, 176, 3), // "num"
QT_MOC_LITERAL(19, 180, 33), // "on_pushButton_Open_Camera_cli..."
QT_MOC_LITERAL(20, 214, 26), // "on_pushButton_Card_clicked"
QT_MOC_LITERAL(21, 241, 12), // "sendfacedata"
QT_MOC_LITERAL(22, 254, 4) // "name"

    },
    "FaceVerify\0Veryfity_face\0\0facenum\0"
    "facename\0Send_Card\0SetImage\0src\0"
    "setCardData\0str\0Get_image\0QImage*\0"
    "image\0on_pushButton_Train_clicked\0"
    "Train_Finish\0Show_Data\0QSqlDatabase*\0"
    "m_db\0num\0on_pushButton_Open_Camera_clicked\0"
    "on_pushButton_Card_clicked\0sendfacedata\0"
    "name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FaceVerify[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       5,    0,   74,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       8,    1,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   81,    2, 0x08 /* Private */,
      13,    0,   84,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,
      15,    2,   86,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      19,    1,   91,    2, 0x02 /* Public */,
      20,    0,   94,    2, 0x02 /* Public */,
      21,    2,   95,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,    7,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::QString,   17,   18,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   22,

       0        // eod
};

void FaceVerify::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FaceVerify *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Veryfity_face((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->Send_Card(); break;
        case 2: _t->SetImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->setCardData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->Get_image((*reinterpret_cast< QImage*(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_Train_clicked(); break;
        case 6: _t->Train_Finish(); break;
        case 7: _t->Show_Data((*reinterpret_cast< QSqlDatabase*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->on_pushButton_Open_Camera_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_Card_clicked(); break;
        case 10: _t->sendfacedata((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FaceVerify::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceVerify::Veryfity_face)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FaceVerify::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceVerify::Send_Card)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FaceVerify::*)(QImage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceVerify::SetImage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FaceVerify::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FaceVerify::setCardData)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FaceVerify::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FaceVerify.data,
    qt_meta_data_FaceVerify,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FaceVerify::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FaceVerify::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FaceVerify.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FaceVerify::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void FaceVerify::Veryfity_face(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FaceVerify::Send_Card()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FaceVerify::SetImage(QImage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FaceVerify::setCardData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
