#ifndef MUSICREGEDITMANAGER_H
#define MUSICREGEDITMANAGER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QObject>
#include "musicglobaldefine.h"

/*! @brief The class of the windows regedit manager.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_CORE_EXPORT MusicRegeditManager
{
public:
    static QString getClassName();
    /*!
     * Get class object name.
     */

    bool isFileAssociate();
    /*!
     * Check current is file associate.
     */
    void setMusicRegeditAssociateFileIcon();
    /*!
     * Set music regedit associate file icon.
     */

    void setDesktopWallAutoStart(bool state);
    /*!
     * Set desktop wall auto start.
     */

    void getDesktopWallControlPanel(QString &originPath, int &originType);
    /*!
     * Get desktop wall control panel.
     */
    void setDesktopWallControlPanel(const QString &originPath, int originType);
    /*!
     * Set desktop wall control panel.
     */

protected:
    bool currentNodeHasExist(const QString &key);
    /*!
     * Check current regedit item has exist.
     */
    void createMusicRegedit(const QString &key);
    /*!
     * Create music regedit item.
     */

};

#endif // MUSICREGEDITMANAGER_H
