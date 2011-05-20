#-------------------------------------------------
#
# Project created by QtCreator 2011-05-20T13:19:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = descrack-core
TEMPLATE = lib
CONFIG += staticlib

SOURCES += descrackcore.cpp \
    rainbowtable.cpp \
    chaingenerator.cpp

HEADERS += descrackcore.h \
    rainbowtable.h \
    chaingenerator.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
