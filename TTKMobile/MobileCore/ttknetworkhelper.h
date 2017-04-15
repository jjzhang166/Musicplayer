#ifndef TTKNETWORKHELPER_H
#define TTKNETWORKHELPER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QObject>
#include "musicobject.h"
#include "musicmobileglobaldefine.h"
#include "musicdownloadquerythreadabstract.h"

/*! @brief The class of the music network helper.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_MOBILE_EXPORT TTKNetworkHelper : public QObject
{
    Q_OBJECT
public:
    enum Type {
        T_Null,              ///*null*/
        T_SearcSong,         ///*search song*/
        T_SearcMovie,        ///*search mv*/
        T_SearcLrc,          ///*search lrc*/
        T_DownloadSong,      ///*download song*/
        T_DownloadSongIndex, ///*download index song*/
        T_DownloadMVIndex    ///*download index mv*/
    };

    explicit TTKNetworkHelper(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    ~TTKNetworkHelper();

    //////////////////////////////////////////////////////
    Q_INVOKABLE void setQueryType(int type);
    /*!
     * Set network query type.
     */
    Q_INVOKABLE void searchSong(const QString &text);
    /*!
     * Search the song online by given name.
     */
    Q_INVOKABLE void searchMovie(const QString &text);
    /*!
     * Search the mv online by given name.
     */
    Q_INVOKABLE void searchLrc(const QString &text);
    /*!
     * Search the lrc online by given name.
     */
    Q_INVOKABLE void downloadSong(const QString &text);
    /*!
     * Download the song online by given name.
     */
    Q_INVOKABLE void setCurrentIndex(int index, const QVariant &data = QVariant());
    /*!
     * Set current play index.
     */
    Q_INVOKABLE QString getSearchedAttributes(int index);
    /*!
     * Get searched information attributes.
     */
    Q_INVOKABLE void setCurrentServer();
    /*!
     * Set current server index.
     */
    Q_INVOKABLE void setCurrentServer(int index);
    /*!
     * Set current server index.
     */
    Q_INVOKABLE int getCurrentServer() const;
    /*!
     * Get current server index.
     */

Q_SIGNALS:
    void networkConnectionStateChanged(bool state);
    /*!
     * Network connection state changed.
     * default status is true, means connected network.
     */
    void clearAllItems();
    /*!
     * Clear all items before the new query start.
     */
    void createSearchedItems(const QString &songname, const QString &artistname);
    /*!
     * Create the current items by song name\ artist name and time.
     */
    void createDownloadSongQuality(int bitrate);
    /*!
     * Create searched downlaod song by bitrate.
     */
    void downForSearchSongFinished(const QString &key, const QString &path);
    /*!
     * Download (cached) song finished.
     */
    void downForSearchMovieFinished(const QString &url);
    /*!
     * Download (search) movie finished.
     */
    void downForSearchLrcFinished(const QString &path);
    /*!
     * Download (search) lrc finished.
     */
    void downForDownloadSongFinished(const QString &path);
    /*!
     * Download (download) song finished.
     */
    void downForDownloadMovieFinished(const QString &path);
    /*!
     * Download (download) movie finished.
     */
    void downLoadDataHasFinished(bool empty);
    /*!
     * Download data just has finished.
     */

private Q_SLOTS:
    void downLoadDataChanged();
    /*!
     * Send download data from net.
     */
    void searchDataDwonloadFinished();
    /*!
     * Search data dwonload finished.
     */
    void createSearchedItems(const MusicSearchedItem &songItem);
    /*!
     * Create the current items by song name\ artist name and time.
     */
    void downloadProgressChanged(float percent, const QString &total, qint64 time);
    /*!
     * Update download percent\ total time and current time progress.
     */

protected:
    void closeWindowNotify();
    /*!
     * Close window notify.
     */
    void dataForDownloadSong();
    /*!
     * Query for download song.
     */

    void downForSearchSong(int index);
    /*!
     * Download for search song.
     */
    void downForSearchMovie(int index);
    /*!
     * Download for search movie.
     */
    void downForSearchLrc(int index);
    /*!
     * Download for search lrc.
     */
    void downForDownloadSong(int bitrate);
    /*!
     * Download for download song.
     */
    void downForDownloadSong(int index, int bitrate);
    /*!
     * Download for download song.
     */
    void downForDownloadMovie(int index, int bitrate);
    /*!
     * Download for download movie.
     */

    int m_currentIndex;
    Type m_queryType;
    MusicDownLoadQueryThreadAbstract *m_queryThread;

};

#endif // TTKNETWORKHELPER_H
