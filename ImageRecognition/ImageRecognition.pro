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
LIBS += $$ROOT_DIR/LibOpenCV/libopencv_imgproc310.dll.a

SOURCES += main.cpp\
        mainwindow.cpp \
    ImageViewer.cpp \
    ProcessingList.cpp \
    Processors/MedianFilter.cpp \
    Processors/MaskFilterBase.cpp \
    Processors/Helpers.cpp \
    ImageLogic.cpp \
    Processors/ScaleColor.cpp \
    Processors/Threshold.cpp \
    Processors/ChannelToGreyScale.cpp \
    Processors/ConvertToHSL.cpp \
    Segmentation/SegmantationLogic.cpp \
    Segmentation/Segment.cpp \
    Moment/MomentCompute.cpp

HEADERS  += mainwindow.h \
    ImageProcessor.h \
    ImageViewer.h \
    ProcessingList.h \
    Processors/MedianFilter.h \
    Processors/MaskFilterBase.h \
    Processors/Helpers.h \
    ImageLogic.h \
    Processors/LowPassFilter.h \
    Processors/ScaleColor.h \
    Processors/ExtractRed.h \
    Processors/ExtractGreen.h \
    Processors/ExtractBlue.h \
    Processors/Threshold.h \
    Processors/ChannelToGreyScale.h \
    Processors/FakeProcessor.h \
    Processors/ConvertToHSL.h \
    Segmentation/SegmantationLogic.h \
    Segmentation/Segment.h \
    Moment/MomentCompute.h \
    Moment/MomentDesc.h

FORMS    += mainwindow.ui
