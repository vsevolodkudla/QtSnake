#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T23:37:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    recordswindow.cpp \
    user.cpp \
    cell.cpp \
    settingswindow.cpp

HEADERS  += mainwindow.h \
    recordswindow.h \
    user.h \
    cell.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    recordswindow.ui \
    settingswindow.ui
