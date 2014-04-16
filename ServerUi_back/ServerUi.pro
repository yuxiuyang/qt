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
    ../common/datadev.cpp \
    linkmgr.cpp
HEADERS += mainwindow.h \
    datadev.h \
    ../include/define.h \
    ../include/link.h \
    linkmgr.h \
    ../common/linkmgr.h \
    ../common/datadev.h \
    network_server.h \
    mainwindow.h \
    datamgr.h \
    linkmgr.h
FORMS += mainwindow.ui
INCLUDEPATH += $$quote(../thread_task)
LIBS += -L../thread_task/Debug \
    -lthread_task
