#include "musicdownloadquerywyalbumthread.h"
#include "musictime.h"
#///QJson import
#include "qjson/parser.h"

#include <QDateTime>

MusicDownLoadQueryWYAlbumThread::MusicDownLoadQueryWYAlbumThread(QObject *parent)
    : MusicDownLoadQueryThreadAbstract(parent)
{
    m_queryServer = "WangYi";
}

QString MusicDownLoadQueryWYAlbumThread::getClassName()
{
    return staticMetaObject.className();
}

void MusicDownLoadQueryWYAlbumThread::startToSearch(QueryType type, const QString &album)
{
    Q_UNUSED(type);
    startToSearch(album);
}

void MusicDownLoadQueryWYAlbumThread::startToSearch(const QString &album)
{
    if(!m_manager)
    {
        return;
    }

    QUrl musicUrl = MusicUtils::Algorithm::mdII(WY_ALBUM_URL, false).arg(album);
    deleteAll();

    QNetworkRequest request;
    request.setUrl(musicUrl);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
    request.setRawHeader("Origin", MusicUtils::Algorithm::mdII(WY_BASE_URL, false).toUtf8());
    request.setRawHeader("Referer", MusicUtils::Algorithm::mdII(WY_BASE_URL, false).toUtf8());
#ifndef QT_NO_SSL
    QSslConfiguration sslConfig = request.sslConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(sslConfig);
#endif
    m_reply = m_manager->get( request );
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()) );
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
                     SLOT(replyError(QNetworkReply::NetworkError)) );
}

void MusicDownLoadQueryWYAlbumThread::downLoadFinished()
{
    if(!m_reply || !m_manager)
    {
        deleteAll();
        return;
    }

    emit clearAllItems();      ///Clear origin items
    m_musicSongInfos.clear();  ///Empty the last search to songsInfo

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll(); ///Get all the data obtained by request

        QJson::Parser parser;
        bool ok;
        QVariant data = parser.parse(bytes, &ok);
        if(ok)
        {
            QVariantMap value = data.toMap();
            if(value["code"].toInt() == 200 && value.contains("album"))
            {
                value = value["album"].toMap();
                QString albumInfo = value["name"].toString() + "<>" +
                                    value["language"].toString() + "<>" +
                                    value["company"].toString() + "<>" +
                        QDateTime::fromMSecsSinceEpoch(value["publishTime"].toULongLong())
                                     .toString("yyyy-MM-dd");
                QVariantList datas = value["songs"].toList();
                foreach(const QVariant &var, datas)
                {
                    if(var.isNull())
                    {
                        continue;
                    }

                    value = var.toMap();
                    MusicObject::MusicSongInfomation musicInfo;
                    musicInfo.m_songName = value["name"].toString();
                    musicInfo.m_timeLength = MusicTime::msecTime2LabelJustified(value["duration"].toInt());
                    musicInfo.m_lrcUrl = MusicUtils::Algorithm::mdII(WY_SONG_LRC_URL, false).arg(value["id"].toInt());

                    QVariantMap albumObject = value["album"].toMap();
                    musicInfo.m_smallPicUrl = albumObject["picUrl"].toString();
                    musicInfo.m_albumId = albumInfo;

                    QVariantList artistsArray = value["artists"].toList();
                    foreach(const QVariant &artistValue, artistsArray)
                    {
                        if(artistValue.isNull())
                        {
                            continue;
                        }
                        QVariantMap artistMap = artistValue.toMap();
                        musicInfo.m_singerName = artistMap["name"].toString();
                    }

                    readFromMusicSongAttribute(&musicInfo, m_manager, value, m_searchQuality, m_queryAllRecords);

                    if(musicInfo.m_songAttrs.isEmpty())
                    {
                        continue;
                    }

                    MusicSearchedItem item;
                    item.m_songname = musicInfo.m_songName;
                    item.m_artistname = musicInfo.m_singerName;
                    item.m_time = musicInfo.m_timeLength;
                    item.m_type = mapQueryServerString();
                    emit createSearchedItems(item);
                    m_musicSongInfos << musicInfo;
                }
            }
        }
    }

    emit downLoadDataChanged(QString());
    deleteAll();
}
