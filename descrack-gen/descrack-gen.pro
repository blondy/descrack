#-------------------------------------------------
#
# Project created by QtCreator 2011-05-20T13:16:08
#
#-------------------------------------------------

QT       -= core gui

LIBS += /usr/lib/libcr.so /usr/lib/libmpl.so /usr/lib/libmpi.so
LIBS += ../descrack-core-build-desktop/libdescrack-core.a

INCLUDEPATH += ../descrack-core/

TARGET = descrack-gen
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    master.cpp \
    entity.cpp \
    slave.cpp

HEADERS += \
    master.h \
    entity.h \
    slave.h
