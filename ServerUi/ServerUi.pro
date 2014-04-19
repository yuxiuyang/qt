# -------------------------------------------------
# Project created by QtCreator 2014-01-22T23:11:42
# -------------------------------------------------
TARGET = ServerUi
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    network_server.cpp \
    linkmgr.cpp \
    datamgr.cpp \
    ../../qt/common/datadev.cpp \
    ../common/recvobject.cpp \
    ../common/fltkLog.cpp
HEADERS += mainwindow.h \
    network_server.h \
    linkmgr.h \
    datamgr.h \
    ../../qt/common/datadev.h \
    ../../qt/include/define.h \
    ../common/recvobject.h \
    ../common/fltkLog.h
FORMS += mainwindow.ui
INCLUDEPATH += $$quote(../thread_task)
LIBS += -L../thread_task/Debug \
    -lthread_task
