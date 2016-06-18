#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T15:17:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VMixBroadcaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomtablewidget.cpp \
    qiptablewidget.cpp

HEADERS  += mainwindow.h \
    qcustomtablewidget.h \
    qiptablewidget.h

FORMS    += mainwindow.ui
