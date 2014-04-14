# -------------------------------------------------
# Project created by QtCreator 2014-01-17T22:04:41
# -------------------------------------------------
TARGET = Simulator
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    mgrdev.cpp \
    basicmgr.cpp \
    spo2mgr.cpp \
    spo2window.cpp \
    file.cpp \
    queue.cpp \
    netdev.cpp \
    network.cpp \
    nibpwindow.cpp \
    nibpmgr.cpp \
    ecgwindow.cpp \
    datadev.cpp
HEADERS += mainwindow.h \
    mgrdev.h \
    basicmgr.h \
    spo2mgr.h \
    spo2window.h \
    file.h \
    queue.h \
    netdev.h \
    network.h \
    ../include/link.h \
    ../include/define.h \
    nibpwindow.h \
    nibpmgr.h \
    ecgwindow.h \
    datadev.h
FORMS += mainwindow.ui \
    spo2window.ui \
    nibpwindow.ui \
    ecgwindow.ui


INCLUDEPATH += $$quote(../thread_task)
LIBS += -L../thread_task/Debug \
    -lthread_task
