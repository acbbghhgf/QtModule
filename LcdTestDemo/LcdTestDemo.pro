#-------------------------------------------------
#
# Project created by QtCreator 2020-03-10T09:54:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LcdTestDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


win32{
INCLUDEPATH += E:\opencv\opencv\cmake-build\install\include \
               E:\opencv\opencv\cmake-build\install\include\opencv2
LIBS += E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_core412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_calib3d412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_dnn412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_features2d412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_flann412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_gapi412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_highgui412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_imgcodecs412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_imgproc412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_ml412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_objdetect412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_photo412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_video412.dll.a \
        E:\opencv\opencv\cmake-build\install\x64\mingw\lib\libopencv_videoio412.dll.a
}

unix{
LIBS += -L /usr/local/lib/  \
        -lopencv_highgui \
        -lopencv_core \
        -lopencv_video \
        -lopencv_imgproc \
}



CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
