#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T17:03:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageRecognition
TEMPLATE = app

ROOT_DIR = D:/ProgramyQT/RozpoznawaniePOBR/

CONFIG += c++11

INCLUDEPATH += $$(OpenCV)build/include/
LIBS += $$ROOT_DIR/LibOpenCV/libopencv_core310.dll.a
LIBS += $$ROOT_DIR/LibOpenCV/libopencv_imgcodecs310.dll.a

SOURCES += main.cpp\
        mainwindow.cpp \
    ImageViewer.cpp \
    ProcessingList.cpp \
    Processors/MedianFilter.cpp \
    Processors/MaskFilterBase.cpp \
    Processors/Helpers.cpp \
    ImageLogic.cpp

HEADERS  += mainwindow.h \
    ImageProcessor.h \
    ImageViewer.h \
    ProcessingList.h \
    Processors/MedianFilter.h \
    Processors/MaskFilterBase.h \
    Processors/Helpers.h \
    ImageLogic.h \
    Processors/LowPassFilter.h

FORMS    += mainwindow.ui
