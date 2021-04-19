/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.0.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MQTTexplorer/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.0.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[34];
    char stringdata0[400];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 23), // "on_actionCopy_triggered"
QT_MOC_LITERAL(60, 24), // "on_actionPaste_triggered"
QT_MOC_LITERAL(85, 22), // "on_actionCut_triggered"
QT_MOC_LITERAL(108, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(132, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(156, 29), // "on_actionSelect_All_triggered"
QT_MOC_LITERAL(186, 35), // "on_actionAbout_Aplication_tri..."
QT_MOC_LITERAL(222, 31), // "on_actionDefault_size_triggered"
QT_MOC_LITERAL(254, 24), // "on_buttonConnect_clicked"
QT_MOC_LITERAL(279, 23), // "on_searchButton_clicked"
QT_MOC_LITERAL(303, 20), // "on_add_topic_clicked"
QT_MOC_LITERAL(324, 23), // "on_copy_topic_2_clicked"
QT_MOC_LITERAL(348, 25), // "on_delete_topic_2_clicked"
QT_MOC_LITERAL(374, 25) // "on_publish_button_clicked"

    },
    "MainWindow\0on_actionQuit_triggered\0\0"
    "on_actionCopy_triggered\0"
    "on_actionPaste_triggered\0"
    "on_actionCut_triggered\0on_actionUndo_triggered\0"
    "on_actionRedo_triggered\0"
    "on_actionSelect_All_triggered\0"
    "on_actionAbout_Aplication_triggered\0"
    "on_actionDefault_size_triggered\0"
    "on_buttonConnect_clicked\0"
    "on_searchButton_clicked\0on_add_topic_clicked\0"
    "on_copy_topic_2_clicked\0"
    "on_delete_topic_2_clicked\0"
    "on_publish_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    0 /* Private */,
       3,    0,  105,    2, 0x08,    1 /* Private */,
       4,    0,  106,    2, 0x08,    2 /* Private */,
       5,    0,  107,    2, 0x08,    3 /* Private */,
       6,    0,  108,    2, 0x08,    4 /* Private */,
       7,    0,  109,    2, 0x08,    5 /* Private */,
       8,    0,  110,    2, 0x08,    6 /* Private */,
       9,    0,  111,    2, 0x08,    7 /* Private */,
      10,    0,  112,    2, 0x08,    8 /* Private */,
      11,    0,  113,    2, 0x08,    9 /* Private */,
      12,    0,  114,    2, 0x08,   10 /* Private */,
      13,    0,  115,    2, 0x08,   11 /* Private */,
      14,    0,  116,    2, 0x08,   12 /* Private */,
      15,    0,  117,    2, 0x08,   13 /* Private */,
      16,    0,  118,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionQuit_triggered(); break;
        case 1: _t->on_actionCopy_triggered(); break;
        case 2: _t->on_actionPaste_triggered(); break;
        case 3: _t->on_actionCut_triggered(); break;
        case 4: _t->on_actionUndo_triggered(); break;
        case 5: _t->on_actionRedo_triggered(); break;
        case 6: _t->on_actionSelect_All_triggered(); break;
        case 7: _t->on_actionAbout_Aplication_triggered(); break;
        case 8: _t->on_actionDefault_size_triggered(); break;
        case 9: _t->on_buttonConnect_clicked(); break;
        case 10: _t->on_searchButton_clicked(); break;
        case 11: _t->on_add_topic_clicked(); break;
        case 12: _t->on_copy_topic_2_clicked(); break;
        case 13: _t->on_delete_topic_2_clicked(); break;
        case 14: _t->on_publish_button_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
