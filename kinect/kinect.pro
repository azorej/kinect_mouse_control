#-------------------------------------------------
#
# Project created by QtCreator 2013-11-24T12:18:08
#
#-------------------------------------------------

QT       -= core gui

QMAKE_CXXFLAGS += -std=c++11

DEFINES += i386

INCLUDEPATH += $$(NITE2_INCLUDE)
INCLUDEPATH += $$(OPENNI2_INCLUDE)

TARGET = kinect
TEMPLATE = lib
CONFIG += staticlib

SOURCES += kinect.cpp \
    hand_tracker.cpp \
    utils.cpp \
    depth_map.cpp \
    video_streamer.cpp

HEADERS += kinect.h \
    hand_tracker.h \
    defs.h \
    utils.h \
    depth_map.h \
    loop_controller_interface.h \
    video_streamer.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist/ -lNiTE2

INCLUDEPATH += $$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist
DEPENDPATH += $$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist

unix:!macx: LIBS += -L$$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist/ -lOpenNI2

INCLUDEPATH += $$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist
DEPENDPATH += $$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist
