# -------------------------------------------------
# Project created by QtCreator 2014-01-22T23:11:42
# -------------------------------------------------
TARGET = ServerUi
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    network_server.cpp \
    linkmgr.cpp \
    datamgr.cpp
HEADERS += mainwindow.h \
    network_server.h \
    ../include/define.h \
    ../include/link.h \
    linkmgr.h \
    datamgr.h
FORMS += mainwindow.ui
INCLUDEPATH += $$quote(../thread_task)
LIBS += -L../thread_task/Debug \
    -lthread_task
