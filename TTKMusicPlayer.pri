# =================================================
# * This file is part of the TTK Music Player project
# * Copyright (c) 2015 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

QT       += core gui xml sql

equals(QT_MAJOR_VERSION, 4){
QT       += network
CONFIG   += gcc
include(TTKExtra/Qt4/qmmp.pri)
}
equals(QT_MAJOR_VERSION, 5){
QT       += widgets multimediawidgets
include(TTKExtra/Qt5/qmmp.pri)
}

UI_DIR = ./.build/ui
MOC_DIR = ./.build/moc
OBJECTS_DIR = ./.build/obj
RCC_DIR = ./.build/rcc

#check Qt version
QT_VER_STRING = $$[QT_VERSION];
QT_VER_STRING = $$split(QT_VER_STRING, ".")
QT_VER_MAJOR = $$member(QT_VER_STRING, 0)
QT_VER_MINOR = $$member(QT_VER_STRING, 1)
QT_VER_PATCH = $$member(QT_VER_STRING, 2)

include(TTKVersion.pri)

win32{
    LIBS += -lIphlpapi -luser32
    equals(QT_MAJOR_VERSION, 5){
        greaterThan(QT_VER_MINOR, 1):QT  += winextras
        msvc{
            LIBS += -L../bin/$$TTKMusicPlayer -lqmmp1 -lTTKUi -lTTKExtras -lTTKWatcher -lzlib
            CONFIG +=c++11
            !contains(QMAKE_TARGET.arch, x86_64){
                 #support on windows XP
                 QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
                 QMAKE_LFLAGS_CONSOLE = /SUBSYSTEM:CONSOLE,5.01
            }
        }

        gcc{
            LIBS += -L../bin/$$TTKMusicPlayer -lqmmp1 -lTTKUi -lTTKExtras -lTTKWatcher -lzlib
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }

    equals(QT_MAJOR_VERSION, 4){
        QT  += multimedia
        gcc{
            LIBS += -L../bin/$$TTKMusicPlayer -lqmmp0 -lTTKUi -lTTKExtras -lTTKWatcher -lzlib
            QMAKE_CXXFLAGS += -std=c++11
            QMAKE_CXXFLAGS += -Wunused-function
            QMAKE_CXXFLAGS += -Wswitch
        }
    }
}

unix:!mac{
    equals(QT_MAJOR_VERSION, 4){
        QMAKE_CXXFLAGS += -I/usr/include/QtMultimediaKit \
                          -I/usr/include/QtMobility
        LIBS += -lQtMultimediaKit
    }

    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wunused-function
    QMAKE_CXXFLAGS += -Wswitch
    LIBS += -L../lib/$$TTKMusicPlayer -lqmmp -lTTKUi -lTTKExtras -lTTKWatcher -lzlib
}

DEFINES += MUSIC_LIBRARY

#########################################
HEADERS += $$PWD/musicglobal.h
INCLUDEPATH += $$PWD
#########################################
contains(CONFIG, TTK_BUILD_LIB){
    include(TTKCore/musicUiKits/MusicUiKits.pri)
}
#########################################
include(TTKThirdParty/TTKThirdParty.pri)
#########################################
include(TTKCore/musicCoreKits/MusicCoreKits.pri)
include(TTKCore/musicNetworkKits/MusicNetworkKits.pri)
include(TTKCore/musicWidgetKits/MusicWidgetKits.pri)
include(TTKCore/musicWidgetCoreKits/MusicWidgetCoreKits.pri)
include(TTKCore/musicSearchKits/MusicSearchKits.pri)
include(TTKCore/musicLrcKits/MusicLrcKits.pri)
include(TTKCore/musicRemoteKits/MusicRemoteKits.pri)
include(TTKCore/musicToolsSetsKits/MusicToolsSetsKits.pri)
include(TTKCore/musicToolsKits/MusicToolsKits.pri)
include(TTKCore/musicUserKits/MusicUserKits.pri)
include(TTKCore/musicVideoKits/MusicVideoKits.pri)
