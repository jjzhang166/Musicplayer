#ifndef CHINESEHELPER_H
#define CHINESEHELPER_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "pinyinresource.h"

class ChineseHelperPrivate;

/*! @brief The class of the simple and traditional chinese characters.
 * @author jiangXiaoBai <2499971906@qq.com>
 */
class MUSIC_EXTRAS_EXPORT ChineseHelper
{
public:
    ChineseHelper();
    /*!
     * Object contsructor.
     */

    QChar convertToSimplifiedChinese(const QChar &c);
    /**
     * The single traditional Chinese characters into simplified Chinese characters
     *
     * @param c Need to convert the traditional Chinese characters
     * @return After the conversion of the simplified Chinese characters
     */

    QChar convertToTraditionalChinese(const QChar &c);
    /**
     * The individual characters converted to traditional Chinese characters
     *
     * @param c The need to convert simplified Chinese characters
     * @return Converted to numerous fonts
     */

    QString convertToSimplifiedChinese(const QString &str);
    /**
     * The traditional Chinese characters into simplified Chinese characters
     *
     * @param str Need to convert the traditional Chinese characters
     * @return Converted to simplified
     */

    QString convertToTraditionalChinese(const QString &str);
    /**
     * Convert the simplified traditional characters
     *
     * @param str The need to convert simplified Chinese characters
     * @return Converted to numerous fonts
     */

    bool isTraditionalChinese(const QChar &c);
    /**
     * To determine whether a character is a traditional character
     *
     * @param c Character needed to be judged
     * @return Is the traditional character returns true, otherwise returns false
     */

    bool isChinese(const QChar &c);
    /**
     * To determine whether a character is a Chinese character
     *
     * @param c Character needed to be judged
     * @return Is the Chinese character returns true, otherwise returns false
     */

    bool containsChinese(const QString &str);
    /**
     * Determine whether the string contains Chinese
     * @param str character string
     * @return Contains the Chinese characters to return to true, or return to false
     */

private:
    TTK_DECLARE_PRIVATE(ChineseHelper)

};

#endif // CHINESEHELPER_H
