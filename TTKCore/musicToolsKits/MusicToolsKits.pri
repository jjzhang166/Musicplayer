# =================================================
# * This file is part of the TTK Music Player project
# * Copyright (c) 2015 - 2017 Greedysky Studio
# * All rights reserved!
# * Redistribution and use of the source code or any derivative
# * works are strictly forbiden.
# =================================================

INCLUDEPATH += $$PWD \
               $$PWD/core

!contains(CONFIG, TTK_NO_MSVC_LINK_NEED){
HEADERS  += \
    $$PWD/core/musicdownloadrecordconfigmanager.h \
    $$PWD/core/musicfilesenderserver.h \
    $$PWD/core/musicfilereceiveserver.h \
    $$PWD/musicsongstoolboxwidget.h \
    $$PWD/musicsongssummariziedwidget.h \
    $$PWD/musictoolsetswidget.h \
    $$PWD/musicconnectmobilewidget.h \
    $$PWD/musicconnecttransferwidget.h \
    $$PWD/musicconnecttransfertablewidget.h \
    $$PWD/musicwebmusicradiolistview.h  \
    $$PWD/musicwebmusicradiowidget.h \
    $$PWD/musiccloudsharedsongwidget.h \
    $$PWD/musiccloudfilemanagerdialog.h \
    $$PWD/musiccloudtablewidget.h \
    $$PWD/musicdownloadrecordwidget.h

}

contains(CONFIG, TTK_BUILD_LIB){
SOURCES += \
    $$PWD/core/musicdownloadrecordconfigmanager.cpp \
    $$PWD/core/musicfilesenderserver.cpp \
    $$PWD/core/musicfilereceiveserver.cpp \
    $$PWD/musicsongstoolboxwidget.cpp \
    $$PWD/musicsongssummariziedwidget.cpp \
    $$PWD/musictoolsetswidget.cpp \
    $$PWD/musicconnectmobilewidget.cpp \
    $$PWD/musicconnecttransferwidget.cpp \
    $$PWD/musicconnecttransfertablewidget.cpp \
    $$PWD/musicwebmusicradiolistview.cpp \
    $$PWD/musicwebmusicradiowidget.cpp \
    $$PWD/musiccloudsharedsongwidget.cpp \
    $$PWD/musiccloudfilemanagerdialog.cpp \
    $$PWD/musiccloudtablewidget.cpp \
    $$PWD/musicdownloadrecordwidget.cpp

}
