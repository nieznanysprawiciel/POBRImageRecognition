#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T17:03:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageRecognition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ImageProcessor.cpp \
    ImageViewer.cpp

HEADERS  += mainwindow.h \
    ImageProcessor.h \
    ImageViewer.h

FORMS    += mainwindow.ui
