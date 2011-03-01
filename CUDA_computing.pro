#-------------------------------------------------
#
# Project created by QtCreator 2011-02-28T16:39:35
#
#-------------------------------------------------

QT       += core gui

TARGET = CUDA_computing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cpuprocessor.cpp \
    subprocessor.cpp

HEADERS  += mainwindow.h \
    cpuprocessor.h \
    subprocessor.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/include/qwt-qt4/"
LIBS += -lqwt-qt4
