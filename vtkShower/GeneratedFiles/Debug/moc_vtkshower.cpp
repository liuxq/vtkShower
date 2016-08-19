/****************************************************************************
** Meta object code from reading C++ file 'vtkshower.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../vtkshower.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vtkshower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_vtkShower_t {
    QByteArrayData data[8];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vtkShower_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vtkShower_t qt_meta_stringdata_vtkShower = {
    {
QT_MOC_LITERAL(0, 0, 9), // "vtkShower"
QT_MOC_LITERAL(1, 10, 11), // "ComboChange"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 17), // "onRadioClickSolid"
QT_MOC_LITERAL(4, 41, 20), // "onRadioClickWareline"
QT_MOC_LITERAL(5, 62, 19), // "onRadioClickSetNode"
QT_MOC_LITERAL(6, 82, 18), // "onRadioClickSetSeg"
QT_MOC_LITERAL(7, 101, 15) // "OnMenuOpenKFile"

    },
    "vtkShower\0ComboChange\0\0onRadioClickSolid\0"
    "onRadioClickWareline\0onRadioClickSetNode\0"
    "onRadioClickSetSeg\0OnMenuOpenKFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vtkShower[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       3,    0,   47,    2, 0x0a /* Public */,
       4,    0,   48,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vtkShower::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vtkShower *_t = static_cast<vtkShower *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ComboChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onRadioClickSolid(); break;
        case 2: _t->onRadioClickWareline(); break;
        case 3: _t->onRadioClickSetNode(); break;
        case 4: _t->onRadioClickSetSeg(); break;
        case 5: _t->OnMenuOpenKFile(); break;
        default: ;
        }
    }
}

const QMetaObject vtkShower::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_vtkShower.data,
      qt_meta_data_vtkShower,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *vtkShower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vtkShower::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_vtkShower.stringdata0))
        return static_cast<void*>(const_cast< vtkShower*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int vtkShower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
