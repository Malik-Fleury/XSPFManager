#-------------------------------------------------
#
# Project created by QtCreator 2018-10-23T09:20:42
#
#-------------------------------------------------

QT       += core gui xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XSPFManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
        src/window/mainwindow.cpp \
    src/data/track.cpp \
    src/data/playlist.cpp \
    src/tools/xspf.cpp

HEADERS += \
    include/window/mainwindow.h \
    include/data/track.h \
    include/data/playlist.h \
    include/tools/xspf.h

FORMS += \
    res/window/mainwindow.ui

unix|win32: LIBS += -L$$PWD/lib/pugixml-1.9/bin/ -lpugixml

INCLUDEPATH += $$PWD/lib/pugixml-1.9/include
DEPENDPATH += $$PWD/lib/pugixml-1.9/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/pugixml-1.9/bin/pugixml.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/pugixml-1.9/bin/libpugixml.a
