#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QDir>
#include <QApplication>
#if defined (Q_OS_ANDROID)
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#endif
#include "musicglobal.h"

#define APPNAME                 "TTKMusicPlayer"
///////////////////////////////////////

#define APPDATA_DIR             "AppData/"
#define DOWNLOADS_DIR           "Downloads/"

#define LRC_DIR                 "MLrc/"
#define MUSIC_DIR               "Music/"
#define MOVIE_DIR               "Movie/"
#define THEME_DIR               "MTheme/"
#define CACHE_DIR               "MCached/"
#define ART_DIR                 "MArt/"
#define RES_DIR                 "MRes/"
#define AVATAR_DIR              "avatar/"
#define USER_THEME_DIR          "theme/"
#define PLUGINS_DIR             "MPlugins/"
#define BACKGROUND_DIR          "MArt/background/"
#define LANGUAGE_DIR            "MLanguage/"
#define TEMPORARY_DIR           "temporary"

#define SKN_FILE                ".skn"
#define JPG_FILE                ".jpg"
#define BMP_FILE                ".bmp"
#define PNG_FILE                ".png"
#define LRC_FILE                ".lrc"
#define KRC_FILE                ".krc"
#define MP3_FILE                ".mp3"
#define CFG_FILE                ".ttk"
#define LST_FILE                ".lis"

#define MAKE_TRANSFORM          "MPlugins/avconv.dll"
#define MAKE_KRC2LRC            "MPlugins/avk2l.dll"
#define MAKE_PLAYER             "MPlugins/avplayer.dll"
#define MAKE_GAIN               "MPlugins/avgain.dll"
#define MAKE_SOUNDTOUCH         "MPlugins/avm2v.dll"
#ifdef Q_OS_UNIX
#define MAKE_NETS               "MPlugins/avnets.dll"
#endif

#define COFIGPATH               "musicconfig.xml"
#define MUSICPATH               "music.lis"
#define NORMALDOWNPATH          "musicdown.ttk"
#define CLOUDDOWNPATH           "musiccloud.ttk"
#define MUSICSEARCH             "musichistory.ttk"
#define DARABASEPATH            "musicuser.dll"
#define USERPATH                "musicuser.ttk"
#define BARRAGEPATH             "musicbarrage.ttk"

///////////////////////////////////////
#if defined (Q_OS_ANDROID)
#  define APPDATA_DIR_FULL      MusicObject::getAppDir() + APPDATA_DIR
#  define DOWNLOADS_DIR_FULL    MusicObject::getAppDir() + DOWNLOADS_DIR
#else
#  define APPDATA_DIR_FULL      MusicObject::getAppDir() + QString("../") + APPDATA_DIR
#  define DOWNLOADS_DIR_FULL    MusicObject::getAppDir() + QString("../") + DOWNLOADS_DIR
#endif

#define LRC_DIR_FULL            DOWNLOADS_DIR_FULL + LRC_DIR
#define MUSIC_DIR_FULL          DOWNLOADS_DIR_FULL + MUSIC_DIR
#define MOVIE_DIR_FULL          DOWNLOADS_DIR_FULL + MOVIE_DIR
#define TEMPORARY_DIR_FULL      DOWNLOADS_DIR_FULL + TEMPORARY_DIR
#define CACHE_DIR_FULL          DOWNLOADS_DIR_FULL + CACHE_DIR
#define ART_DIR_FULL            DOWNLOADS_DIR_FULL + ART_DIR
#define BACKGROUND_DIR_FULL     DOWNLOADS_DIR_FULL + BACKGROUND_DIR

#define COFIGPATH_FULL          APPDATA_DIR_FULL + COFIGPATH
#define MUSICPATH_FULL          APPDATA_DIR_FULL + MUSICPATH
#define NORMALDOWNPATH_FULL     APPDATA_DIR_FULL + NORMALDOWNPATH
#define CLOUDDOWNPATH_FULL      APPDATA_DIR_FULL + CLOUDDOWNPATH
#define MUSICSEARCH_FULL        APPDATA_DIR_FULL + MUSICSEARCH
#define DARABASEPATH_FULL       APPDATA_DIR_FULL + DARABASEPATH
#define USERPATH_FULL           APPDATA_DIR_FULL + USERPATH
#define BARRAGEPATH_FULL        APPDATA_DIR_FULL + BARRAGEPATH
#define AVATAR_DIR_FULL         APPDATA_DIR_FULL + AVATAR_DIR
#define USER_THEME_DIR_FULL     APPDATA_DIR_FULL + USER_THEME_DIR

#define THEME_DIR_FULL          MusicObject::getAppDir() + THEME_DIR
#define PLUGINS_DIR_FULL        MusicObject::getAppDir() + PLUGINS_DIR
#define LANGUAGE_DIR_FULL       MusicObject::getAppDir() + LANGUAGE_DIR

#define MAKE_TRANSFORM_FULL     MusicObject::getAppDir() + MAKE_TRANSFORM
#define MAKE_KRC2LRC_FULL       MusicObject::getAppDir() + MAKE_KRC2LRC
#define MAKE_PLAYER_FULL        MusicObject::getAppDir() + MAKE_PLAYER
#define MAKE_GAIN_FULL          MusicObject::getAppDir() + MAKE_GAIN
#define MAKE_SOUNDTOUCH_FULL    MusicObject::getAppDir() + MAKE_SOUNDTOUCH
#ifdef Q_OS_UNIX
#define MAKE_NETS_FULL          MusicObject::getAppDir() + MAKE_NETS
#endif

///////////////////////////////////////
#define WINDOW_WIDTH_MIN        1033
#define WINDOW_HEIGHT_MIN       660
///////////////////////////////////////
#define DEFAULT_INDEX_LEVEL0    -1
#define DEFAULT_INDEX_LEVEL1    -999
#define DEFAULT_INDEX_LEVEL2    -888
#define DEFAULT_INDEX_LEVEL3    -777
#define DEFAULT_INDEX_LEVEL4    -666
#define DEFAULT_INDEX_LEVEL5    -555
///////////////////////////////////////
#define STRING_SPLITER          "*|||*"
///////////////////////////////////////

/*! @brief The namespace of the application object.
 * @author Greedysky <greedysky@163.com>
 */
namespace MusicObject
{
    typedef struct MusicSongAttribute
    {
        int m_bitrate;
        QString m_format;
        QString m_url;
        QString m_size;
        QString m_duration;

        bool operator< (const MusicSongAttribute &other) const
        {
            return m_bitrate < other.m_bitrate;
        }
        bool operator== (const MusicSongAttribute &other) const
        {
            return m_bitrate == other.m_bitrate;
        }
    }MusicSongAttribute;
    TTK_DECLARE_LISTS(MusicSongAttribute)

    ///////////////////////////////////////

    typedef struct MusicSongInfomation
    {
        MusicSongAttributes m_songAttrs;
        QString m_songId;
        QString m_albumId;
        QString m_artistId;
        QString m_lrcUrl;
        QString m_smallPicUrl;
        QString m_singerName;
        QString m_songName;
        QString m_timeLength;
    }MusicSongInfomation;
    TTK_DECLARE_LISTS(MusicSongInfomation)
    ///////////////////////////////////////

    enum DownLoadMode
    {
        DW_Null,           ///*network null*/
        DW_DisConnection,  ///*network disable*/
        DW_DownLoading,    ///*network download*/
        DW_Buffing,        ///*network buffing*/
        DW_Waiting         ///*network waiting*/
    };

    enum SongPlayMode
    {
        MC_PlayOrder = 1,   ///*play order*/
        MC_PlayRandom,      ///*play random*/
        MC_PlayListLoop,    ///*play list loop*/
        MC_PlayOneLoop,     ///*play single loop*/
        MC_PlayOnce         ///*play just once*/
    };

    enum FontStyleMode
    {
        FT_Bold =       0x00001,   ///*font bold*/
        FT_Italic =     0x00002,   ///*font italic*/
        FT_Underline =  0x00004,   ///*font underline*/
        FT_Overline =   0x00008,   ///*font overline*/
        FT_StrikeOut =  0x00010,   ///*font strikeOut*/
        FT_FixedPitch = 0x00020,   ///*font fixedPitch*/
        FT_Kerningt =   0x00040    ///*font kerningt*/
    };

    static QString getAppDir()
    {
#if defined (Q_OS_ANDROID)
        QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment",
                                                                           "getExternalStorageDirectory",
                                                                           "()Ljava/io/File;");
        QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );
        QString path = mediaPath.toString() + "/TTKMobile/";
        if(!QDir().exists(path))
        {
            QDir().mkpath(path);
        }
        return path;
#else
        return QApplication::applicationDirPath() + "/";
#endif
    }
    /*!
     * Get application dir.
     */

}

#endif // MUSICOBJECT_H
