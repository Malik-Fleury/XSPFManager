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
    src/tools/xspf.cpp \
    lib/pugixml-1.9/src/pugixml.cpp \
    src/widgets/panelexport.cpp \
    src/widgets/table/playlisttablewidget.cpp \
    src/commands/addtrackcommand.cpp \
    src/commands/movetrackcommand.cpp \
    src/commands/removetrackcommand.cpp

HEADERS += \
    include/window/mainwindow.h \
    include/data/track.h \
    include/data/playlist.h \
    include/tools/xspf.h \
    lib/pugixml-1.9/src/pugixml.hpp \
    lib/pugixml-1.9/src/pugiconfig.hpp \
    include/widgets/panelexport.h \
    include/widgets/table/playlisttablewidget.h \
    include/commands/addtrackcommand.h \
    include/commands/movetrackcommand.h \
    include/commands/removetrackcommand.h

TRANSLATIONS = xspfmanager_en.ts \
        xspfmanager_fr.ts

FORMS += \
    res/window/mainwindow.ui \
    res/widgets/panelexport.ui
