#ifndef MUSICLOCALSONGSTABLEWIDGET_H
#define MUSICLOCALSONGSTABLEWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicsongslistabstracttablewidget.h"

/*! @brief The class of the lcal songs table widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicLocalSongsTableWidget : public MusicSongsListAbstractTableWidget
{
    Q_OBJECT
public:
    explicit MusicLocalSongsTableWidget(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */
    virtual ~MusicLocalSongsTableWidget();

    static QString getClassName();
    /*!
     * Get class object name.
     */

    void clearShowlist();
    /*!
     * Clear show list.
     */
    void clearShowPath();
    /*!
     * Clear show path.
     */
    void createShowlist();
    /*!
     * Create show list.
     */
    void createShowPath();
    /*!
     * Create show path.
     */
    void addShowlistItems(const QFileInfoList &path);
    /*!
     * Add show list items.
     */
    void addShowPathItems(const QFileInfoList &path);
    /*!
     * Add show path items.
     */

public Q_SLOTS:
    virtual void listCellClicked(int row, int column) override;
    /*!
     * Table widget list cell click.
     */
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    /*!
     * Override the widget event.
     */

};

#endif // MUSICLOCALSONGSTABLEWIDGET_H
