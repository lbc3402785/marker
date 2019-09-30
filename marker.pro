#-------------------------------------------------
#
# Project created by QtCreator 2019-09-29T09:38:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = marker
TEMPLATE = app
OBJECTS_DIR=$${PWD}/build
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
ZLIB_INCLUDE_DIRS="C:\Program Files (x86)\zlib\include"
ZLIB_LIBRARY_DIRS="C:\Program Files (x86)\zlib\lib"
OPENCV_INCLUDE_DIRS=D:\soft\opencv3\build\include
OPENCV_LIBRARY_DIRS=D:\soft\opencv3\build\x64\vc14\lib
INCLUDEPATH+=$$OPENCV_INCLUDE_DIRS
INCLUDEPATH+=$$ZLIB_INCLUDE_DIRS
LIBS+=-L$$OPENCV_LIBRARY_DIRS -lopencv_world344
LIBS+=-L$$ZLIB_LIBRARY_DIRS -lzlib
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        MyLabel.cpp \
        cnpy.cpp \
        imagelabel.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        MyLabel.h \
        cnpy.h \
        imagelabel.h \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
