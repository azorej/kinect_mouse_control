#-------------------------------------------------
#
# Project created by QtCreator 2013-11-24T18:35:05
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

DEFINES += i386

INCLUDEPATH += $$(NITE2_INCLUDE)
INCLUDEPATH += $$(OPENNI2_INCLUDE)

TARGET = qt_hand_cursor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    depth_view.cpp \
    simple_loop_controller.cpp

HEADERS  += mainwindow.h \
    logging_system.h \
    depth_view.h \
    simple_loop_controller.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -lGLU -lX11

unix:!macx: LIBS += -L/home/azorej/projects/builds/kinect_mouse_control/kinect_lib/debug -lkinect

unix:!macx: LIBS += -L$$(NITE2_INCLUDE)/../Redist/ -lNiTE2

unix:!macx: LIBS += -L$$(OPENNI2_INCLUDE)/../Redist/ -lOpenNI2
