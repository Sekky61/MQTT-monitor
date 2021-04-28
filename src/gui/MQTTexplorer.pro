QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera_tile.cpp \
    dash_tile.cpp \
    dialog.cpp \
    fulltext_tile.cpp \
    humidity_tile.cpp \
    light_tile.cpp \
    main.cpp \
    mainwindow.cpp \
    new_connection.cpp \
    snapshot.cpp \
    temperature_tile.cpp \
    thermostat_tile.cpp

HEADERS += \
    camera_tile.h \
    dash_tile.h \
    dialog.h \
    fulltext_tile.h \
    humidity_tile.h \
    light_tile.h \
    mainwindow.h \
    new_connection.h \
    snapshot.h \
    temperature_tile.h \
    thermostat_tile.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    new_connection.ui \
    snapshot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
