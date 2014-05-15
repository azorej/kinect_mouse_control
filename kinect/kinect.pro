#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T12:18:08
#
#-------------------------------------------------

QT       -= core gui

TARGET = kinect
TEMPLATE = lib
CONFIG += staticlib

SOURCES += kinect.cpp \
    hand_tracker.cpp \
    utils.cpp \
    viewer.cpp

HEADERS += kinect.h \
    hand_tracker.h \
    defs.h \
    utils.h \
    depth_map.h \
    viewer.h \
    loop_controller_interface.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
