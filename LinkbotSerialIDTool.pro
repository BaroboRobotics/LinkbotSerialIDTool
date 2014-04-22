#-------------------------------------------------
#
# Project created by QtCreator 2014-04-22T15:30:06
#
#-------------------------------------------------

QT       += core gui

VERSION = 0.0.2

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LinkbotSerialIDTool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

INCLUDEPATH += ../stage/include

LIBS += -L../stage/lib -lbarobo

FORMS    += mainwindow.ui
