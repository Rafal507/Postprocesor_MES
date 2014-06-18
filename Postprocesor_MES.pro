#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T23:24:04
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Postprocesor_MES
TEMPLATE = app
CONFIG   += c++11

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    objectrotation.cpp \
    preparedata.cpp \
    readvtkdata.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    objectrotation.h \
    preparedata.h \
    readvtkdata.h \
    EnableLoop.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:/Program Files (x86)/MPICH2/include"
LIBS += "C:/Program Files (x86)/MPICH2/lib/mpi.lib"
