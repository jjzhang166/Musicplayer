#ifndef MUSICPREVIEWLABEL_H
#define MUSICPREVIEWLABEL_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicclickedlabel.h"

/*! @brief The class of the lrc color preview label.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicColorPreviewLabel : public MusicClickedLabel
{
    Q_OBJECT
public:
    explicit MusicColorPreviewLabel(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setLinearGradient(const QList<QColor> &colors);
    /*!
     * Set linear gradient and fg and bg.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */
    QLinearGradient m_linearGradient;

};


typedef struct MUSIC_WIDGET_EXPORT MusicPreviewLabelItem
{
    QString m_family;
    int m_size;
    int m_type;
    QList<QColor> m_fg;
    QList<QColor> m_bg;
}MusicPreviewLabelItem;

/*! @brief The class of the lrc setting preview label.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicPreviewLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MusicPreviewLabel(QWidget *parent = 0);
    /*!
     * Object contsructor.
     */

    static QString getClassName();
    /*!
     * Get class object name.
     */
    void setLinearGradient(const MusicPreviewLabelItem &item);
    /*!
     * Set linear gradient item.
     */
    void setLinearGradient(const QList<QColor> &fg, const QList<QColor> &bg);
    /*!
     * Set linear gradient and fg and bg.
     */
    void setTransparent(int trans) { m_transparent = trans;}
    /*!
     * Set current transparent.
     */

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    /*!
     * Override the widget event.
     */

    QFont m_font;
    QLinearGradient m_linearGradient;
    QLinearGradient m_maskLinearGradient;
    int m_transparent;

};

#endif // MUSICPREVIEWLABEL_H
