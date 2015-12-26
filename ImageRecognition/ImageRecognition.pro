#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T17:03:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageRecognition
TEMPLATE = app


CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ImageViewer.cpp \
    ProcessingList.cpp \
    Processors/MedianFilter.cpp

HEADERS  += mainwindow.h \
    ImageProcessor.h \
    ImageViewer.h \
    ProcessingList.h \
    Processors/MedianFilter.h

FORMS    += mainwindow.ui
