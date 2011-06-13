#-------------------------------------------------
#
# Project created by QtCreator 2011-05-20T13:19:08
#
#-------------------------------------------------

QT       -= core ui

LIBS += ../descrack-core-build-desktop/libdescrack-core.a
LIBS += -lcrypt

INCLUDEPATH += ../descrack-core/

TARGET = descrack-table
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
