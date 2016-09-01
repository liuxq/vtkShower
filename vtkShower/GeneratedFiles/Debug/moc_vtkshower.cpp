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
    QByteArrayData data[12];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vtkShower_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vtkShower_t qt_meta_stringdata_vtkShower = {
    {
QT_MOC_LITERAL(0, 0, 9), // "vtkShower"
QT_MOC_LITERAL(1, 10, 17), // "onPartComboChange"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "onDataComboChange"
QT_MOC_LITERAL(4, 47, 17), // "onRadioClickSolid"
QT_MOC_LITERAL(5, 65, 20), // "onRadioClickWareline"
QT_MOC_LITERAL(6, 86, 19), // "onRadioClickSetNode"
QT_MOC_LITERAL(7, 106, 18), // "onRadioClickSetSeg"
QT_MOC_LITERAL(8, 125, 21), // "onRadioClickPointData"
QT_MOC_LITERAL(9, 147, 21), // "onRadioClickShellData"
QT_MOC_LITERAL(10, 169, 15), // "OnMenuOpenKFile"
QT_MOC_LITERAL(11, 185, 12) // "OnButtonPlay"

    },
    "vtkShower\0onPartComboChange\0\0"
    "onDataComboChange\0onRadioClickSolid\0"
    "onRadioClickWareline\0onRadioClickSetNode\0"
    "onRadioClickSetSeg\0onRadioClickPointData\0"
    "onRadioClickShellData\0OnMenuOpenKFile\0"
    "OnButtonPlay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vtkShower[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       3,    1,   67,    2, 0x0a /* Public */,
       4,    0,   70,    2, 0x0a /* Public */,
       5,    0,   71,    2, 0x0a /* Public */,
       6,    0,   72,    2, 0x0a /* Public */,
       7,    0,   73,    2, 0x0a /* Public */,
       8,    0,   74,    2, 0x0a /* Public */,
       9,    0,   75,    2, 0x0a /* Public */,
      10,    0,   76,    2, 0x0a /* Public */,
      11,    0,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 0: _t->onPartComboChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onDataComboChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onRadioClickSolid(); break;
        case 3: _t->onRadioClickWareline(); break;
        case 4: _t->onRadioClickSetNode(); break;
        case 5: _t->onRadioClickSetSeg(); break;
        case 6: _t->onRadioClickPointData(); break;
        case 7: _t->onRadioClickShellData(); break;
        case 8: _t->OnMenuOpenKFile(); break;
        case 9: _t->OnButtonPlay(); break;
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
