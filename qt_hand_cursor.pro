#-------------------------------------------------
#
# Project created by QtCreator 2013-11-24T18:35:05
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += $$(NITE2_INCLUDE)
INCLUDEPATH += $$(OPENNI2_INCLUDE)

DEFINES += i386

TARGET = qt_hand_cursor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hand_tracker.cpp \
    depth_view.cpp \
    mouse_control.cpp \
    simple_loop_controller.cpp

HEADERS  += mainwindow.h \
    hand_tracker.h \
    logging_system.h \
    depth_view.h \
    defs.h \
    utils.h \
    mouse_control.h \
    hand_buffer.h \
    simple_loop_controller.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist/ -lNiTE2

INCLUDEPATH += $$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist
DEPENDPATH += $$PWD/../../../libs/nite/NiTE-Linux-x86-2.2/Redist

unix:!macx: LIBS += -L$$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist/ -lOpenNI2

INCLUDEPATH += $$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist
DEPENDPATH += $$PWD/../../../libs/openni/OpenNI-Linux-x86-2.2/Redist

unix:!macx: LIBS += -lGLU -lX11

LIBS += kinect
