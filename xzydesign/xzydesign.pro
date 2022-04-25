#-------------------------------------------------
#
# Project created by QtCreator 2022-03-31T02:02:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xzydesign
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialogmphtxt.cpp \
    dialogmaincontrol.cpp \
    dialogsolverthboundary.cpp \
    dialogsolveriboundary.cpp \
    dialogchoosetype.cpp \
    dialogsolvereboundary.cpp \
    dialogtimecontrol.cpp

HEADERS += \
        mainwindow.h \
    dialogmphtxt.h \
    dialogmaincontrol.h \
    dialogsolverthboundary.h \
    dialogsolveriboundary.h \
    dialogchoosetype.h \
    dialogsolvereboundary.h \
    dialogtimecontrol.h

FORMS += \
        mainwindow.ui \
    dialogmphtxt.ui \
    dialogmaincontrol.ui \
    dialogsolverthboundary.ui \
    dialogsolveriboundary.ui \
    dialogchoosetype.ui \
    dialogsolvereboundary.ui \
    dialogtimecontrol.ui
