#ifndef MUSICDOWNLOADQUERYTHREADABSTRACT_H
#define MUSICDOWNLOADQUERYTHREADABSTRACT_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicobject.h"
#include "musicdownloadpagingthread.h"

typedef struct MUSIC_NETWORK_EXPORT MusicSearchedItem
{
    QString m_songname;
    QString m_artistname;
    QString m_time;
    QString m_type;
}MusicSearchedItem;
TTK_DECLARE_LISTS(MusicSearchedItem)

typedef struct MUSIC_NETWORK_EXPORT MusicPlaylistItem
{
    QString m_id;
    QString m_name;
    QString m_nickname;
    QString m_coverUrl;
    QString m_playCount;
    QString m_description;
    QString m_updateTime;
    QString m_tags;

    MusicPlaylistItem()
    {
        m_id = "-";
        m_name = "-";
        m_nickname = "-";
        m_coverUrl = "-";
        m_playCount = "-";
        m_description = "-";
        m_updateTime = "-";
        m_tags = "-";
    }
}MusicPlaylistItem;
TTK_DECLARE_LISTS(MusicPlaylistItem)

/*! @brief The class to abstract query download data from net.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadQueryThreadAbstract : public MusicDownLoadPagingThread
{
    Q_OBJECT
public:
    enum QueryType
    {
        MusicQuery, ///*query music*/
        MovieQuery, ///*query movie*/
        LrcQuery,   ///*query lrc*/
        OtherQuery, ///*query external*/
    };

    explicit MusicDownLoadQueryThreadAbstract(QObject *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicDownLoadQueryThreadAbstract();

    static QString getClassName();
    /*!
     * Get class object name.
     */

    virtual void startToSearch(QueryType type, const QString &text) = 0;
    /*!
     * Start to search data from name and type.
     * Subclass should implement this function.
     */

    inline void setSearchQuality(const QString &qual) { m_searchQuality = qual;}
    /*!
     * Set search data quality.
     */
    inline QString getSearchQuality() const { return m_searchQuality;}
    /*!
     * Get search data quality.
     */
    inline void setQueryAllRecords(bool state) { m_queryAllRecords = state;}
    /*!
     * Set wheather query all quality of records.
     */
    inline bool getQueryAllRecords() const { return m_queryAllRecords;}
    /*!
     * Get query all records flag.
     */
    inline void setQuerySimplify(bool state) { m_querySimplify = state;}
    /*!
     * Set query simplify mode.
     */
    inline bool getQuerySimplify() const { return m_querySimplify;}
    /*!
     * Get query simplify flag.
     */
    inline void setQueryExtraMovie(bool state) { m_queryExtraMovie = state;}
    /*!
     * Set query extra movie flag.
     */
    inline QueryType getQueryType() const { return m_currentType;}
    /*!
     * Return the current song query type.
     */
    inline QString getQueryServer() const { return m_queryServer;}
    /*!
     * Return the current song query server.
     */
    inline QString getSearchedText() const { return m_searchText;}
    /*!
     * Return the current song name.
     */
    inline const MusicObject::MusicSongInfomations& getMusicSongInfos() const { return m_musicSongInfos; }
    /*!
     * Return the current song container.
     */

Q_SIGNALS:
    void clearAllItems();
    /*!
     * Clear all items before the new query start.
     */
    void createSearchedItems(const MusicSearchedItem &songItem);
    /*!
     * Create the current items by song name\ artist name and time.
     */

protected:
    QString mapQueryServerString() const;
    /*!
     * Map query server string.
     */

    MusicObject::MusicSongInfomations m_musicSongInfos;
    QString m_searchText, m_searchQuality;
    QString m_queryServer;
    QueryType m_currentType;
    bool m_queryAllRecords, m_querySimplify, m_queryExtraMovie;

};

#endif // MUSICDOWNLOADQUERYTHREADABSTRACT_H
