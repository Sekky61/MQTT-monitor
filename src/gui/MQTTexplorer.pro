QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutapplication.cpp \
    client.cpp \
    error_messages.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    new_connection.cpp \
    snapshot_manager.cpp \
    topicmodel.cpp

HEADERS += \
    aboutapplication.h \
    client.h \
    error_messages.h \
    dialog.h \
    mainwindow.h \
    new_connection.h \
    snapshot_manager.h \
    topicmodel.h


HEADERS += ../logic/message_system.hpp
SOURCES += ../logic/message_system.cpp

FORMS += \
    dialog.ui \
    mainwindow.ui \
    new_connection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

unix|win32: LIBS += -lpaho-mqttpp3 -lpaho-mqtt3as
