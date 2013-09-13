#-------------------------------------------------
#
# Project created by QtCreator 2013-09-11T11:15:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BroadSign
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp

HEADERS  += mainwindow.h \
    tablemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
