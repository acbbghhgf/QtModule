QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application/drawPic/mainwidget.cpp \
    application/main/main.cpp \
    application/socket/wwk_mod_tcpserver.cpp \
    framwork/main/wwk_sched.cpp \
    platform/encode/encode.cpp \
    platform/sys/signal_init.c \
    platform/sys/sys_init.cpp

HEADERS += \
    application/drawPic/mainwidget.h \
    application/main/main.h \
    application/socket/wwk_mod_tcpserver.h \
    framwork/main/wwk_mod.h \
    framwork/main/wwk_sched.h \
    platform/base/base.h \
    platform/base/wwk_type.h \
    platform/encode/encode.h \
    platform/sys/signal_init.h \
    platform/sys/sys_init.h \
    platform/sys/thread_queue.h

FORMS += \
    mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
