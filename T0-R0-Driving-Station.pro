#-------------------------------------------------
#
# Project created by QtCreator 2018-07-01T17:40:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = T0-R0-Driving-Station
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


###################
# QT-GStreamer
#
# Tell qmake to use pkg-config to find QtGStreamer.
CONFIG += link_pkgconfig

# Now tell qmake to link to QtGStreamer and also use its include path and Cflags.
contains(QT_VERSION, ^4\\..*) {
  PKGCONFIG += QtGStreamer-1.0 QtGStreamerUi-1.0
}
contains(QT_VERSION, ^5\\..*) {
  PKGCONFIG += Qt5GStreamer-1.0 Qt5GStreamerUi-1.0
  QT += widgets
}


# Recommended if you are using g++ 4.5 or later. Must be removed for other compilers.
#QMAKE_CXXFLAGS += -std=c++0x

# Recommended, to avoid possible issues with the "emit" keyword
# You can otherwise also define QT_NO_EMIT, but notice that this is not a documented Qt macro.
DEFINES += QT_NO_KEYWORDS

# link against QtDeclarative and QtOpenGL
#QT += declarative opengl
####################

# TCPSERVER
QT += network

# GAMEPAD
QT += gamepad
#CONFIG += c++11

RESOURCES     += resources.qrc

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui.cpp \
    voipvideowidget.cpp \
    joystick.cpp \
    TcpClient.cpp \
    TcpServer.cpp \
    gamepad.cpp

HEADERS += \
    mainwindow.h \
    ui.h \
    voipvideowidget.h \
    joystick.h \
    TcpClient.h \
    TcpServer.h \
    gamepad.h \
    config.h

FORMS += \
    mainwindow.ui
