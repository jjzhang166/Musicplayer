#include "musiclrcsearchtablewidget.h"
#include "musicmessagebox.h"
#include "musicitemdelegate.h"
#include "musicdownloadqueryfactory.h"
#include "musicgiflabelwidget.h"
#include "musiccoreutils.h"

MusicLrcSearchTableWidget::MusicLrcSearchTableWidget(QWidget *parent)
    : MusicQueryItemTableWidget(parent)
{
    setColumnCount(7);
    QHeaderView *headerview = horizontalHeader();
    headerview->resizeSection(0, 30);
    headerview->resizeSection(1, 213);
    headerview->resizeSection(2, 181);
    headerview->resizeSection(3, 55);
    headerview->resizeSection(4, 24);
    headerview->resizeSection(5, 24);
    headerview->resizeSection(6, 24);
}

MusicLrcSearchTableWidget::~MusicLrcSearchTableWidget()
{
    clearAllItems();
}

QString MusicLrcSearchTableWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicLrcSearchTableWidget::startSearchQuery(const QString &text)
{
    if(!M_NETWORK_PTR->isOnline())
    {   //no network connection
        clearAllItems();
        emit showDownLoadInfoFor(MusicObject::DW_DisConnection);
        return;
    }
    MusicQueryItemTableWidget::startSearchQuery(text);
    connect(m_downLoadManager, SIGNAL(downLoadDataChanged(QString)), SIGNAL(resolvedSuccess()));
    m_loadingLabel->show();
    m_loadingLabel->start();
    m_downLoadManager->startToSearch(MusicDownLoadQueryThreadAbstract::LrcQuery, text);
}

void MusicLrcSearchTableWidget::musicDownloadLocal(int row)
{
    if( row < 0 || (row >= rowCount() - 1))
    {
        MusicMessageBox message;
        message.setText(tr("Please Select One Item First!"));
        message.exec();
        return;
    }

    MusicObject::MusicSongInfomations musicSongInfos(m_downLoadManager->getMusicSongInfos());
    ///download lrc
    MusicDownLoadThreadAbstract *lrcDownload = M_DOWNLOAD_QUERY_PTR->getDownloadLrcThread(musicSongInfos[row].m_lrcUrl,
                             MusicUtils::Core::lrcPrefix() + m_downLoadManager->getSearchedText() + LRC_FILE,
                             MusicDownLoadThreadAbstract::Download_Lrc, this);
    connect(lrcDownload, SIGNAL(downLoadDataChanged(QString)),
                         SIGNAL(lrcDownloadStateChanged(QString)));
    lrcDownload->startToDownload();
}

void MusicLrcSearchTableWidget::listCellEntered(int row, int column)
{
    if(column == 6)
    {
        setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
        unsetCursor();
    }

    MusicQueryItemTableWidget::listCellEntered(row, column);
}

void MusicLrcSearchTableWidget::listCellClicked(int row, int column)
{
    MusicQueryItemTableWidget::listCellClicked(row, column);
    switch(column)
    {
        case 6:
            musicDownloadLocal(row);
            break;
        default:
            break;
    }
}

void MusicLrcSearchTableWidget::clearAllItems()
{
    MusicQueryItemTableWidget::clearAllItems();
    setColumnCount(7);
}

void MusicLrcSearchTableWidget::createSearchedItems(const MusicSearchedItem &songItem)
{
    int count = rowCount();
    setRowCount(count + 1);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(MUSIC_CHECK_ROLE, false);
    setItem(count, 0, item);

                      item = new QTableWidgetItem;
    item->setText(MusicUtils::Widget::elidedText(font(), songItem.m_songname, Qt::ElideRight, 170));
    item->setTextColor(QColor(100, 100, 100));
    item->setTextAlignment(Qt::AlignCenter);
    item->setToolTip(songItem.m_songname);
    setItem(count, 1, item);

                      item = new QTableWidgetItem;
    item->setText(MusicUtils::Widget::elidedText(font(), songItem.m_artistname, Qt::ElideRight, 144));
    item->setTextColor(QColor(100, 100, 100));
    item->setTextAlignment(Qt::AlignCenter);
    item->setToolTip(songItem.m_artistname);
    setItem(count, 2, item);

                      item = new QTableWidgetItem(songItem.m_time);
    item->setTextColor(QColor(100, 100, 100));
    item->setTextAlignment(Qt::AlignCenter);
    setItem(count, 3, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(randToGetStrength()));
    setItem(count, 4, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(QString::fromUtf8(":/tiny/lb_server_type")));
    item->setToolTip(songItem.m_type);
    setItem(count, 5, item);

                      item = new QTableWidgetItem;
    item->setIcon(QIcon(QString::fromUtf8(":/contextMenu/btn_download")));
    setItem(count, 6, item);
}

void MusicLrcSearchTableWidget::itemDoubleClicked(int row, int column)
{
    if(column <= 0)
    {
        return;
    }
    musicDownloadLocal(row);
}

void MusicLrcSearchTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
    MusicQueryItemTableWidget::contextMenuEvent(event);
    QMenu rightClickMenu(this);
    createContextMenu(rightClickMenu);

    rightClickMenu.exec(QCursor::pos());
}
