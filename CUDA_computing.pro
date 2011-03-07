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
    subprocessor.cpp \
    gpuprocessor.cpp

CUDASOURCES = gpu_processor.cu

HEADERS  += mainwindow.h \
    cpuprocessor.h \
    subprocessor.h \
    gpuprocessor.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/include/qwt-qt4/"
LIBS += -lqwt-qt4 -L/usr/local/cuda/lib64 -lcudart

cu.output = ${QMAKE_FILE_BASE}.o
cu.commands = /usr/local/cuda/bin/nvcc -c ${QMAKE_FILE_NAME} -o ${QMAKE_FILE_OUT}
cu.input = CUDASOURCES
cu.CONFIG += no_link
cu.variable_out = OBJECTS

QMAKE_EXTRA_COMPILERS += cu
