#include "musicsongslistplaywidget.h"
#include "musicsongtag.h"
#include "musicsongstoolitemrenamedwidget.h"
#include "musicobject.h"
#include "musicuiobject.h"
#include "musicstringutils.h"
#include "musicwidgetutils.h"
#include "musicnumberdefine.h"
#include "musicsettingmanager.h"
#include "musicapplication.h"
#include "musicleftareawidget.h"
#include "musictinyuiobject.h"
#include "musicsplititemclickedlabel.h"

#include <QMenu>
#include <QTimer>

MusicSongsListPlayWidget::MusicSongsListPlayWidget(int index, QWidget *parent)
    : QWidget(parent), m_renameLine(nullptr)
{
    QPalette pal = palette();
    pal.setBrush(QPalette::Base,QBrush(QColor(0, 0, 0, 40)));
    setPalette(pal);
    setAutoFillBackground(true);

    m_currentPlayIndex = index;
    m_totalTime = "/00:00";

    QPushButton *addButton = new QPushButton(this);
    addButton->setGeometry(2, 25, 16, 16);
    addButton->setStyleSheet(MusicUIObject::MKGTinyBtnPlayLater);
    addButton->setCursor(QCursor(Qt::PointingHandCursor));
    addButton->setToolTip(tr("playLater"));

    m_artPictureLabel = new QLabel(this);
    m_artPictureLabel->setFixedSize(60, 60);
    m_artPictureLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_artPictureLabel->setGeometry(20, 0, 60, 60);

    m_songNameLabel = new MusicSplitItemClickedLabel(this);
    m_songNameLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_songNameLabel->setStyleSheet(MusicUIObject::MColorStyle01);
    m_songNameLabel->setGeometry(85, 5, 200, 25);

    m_timeLabel = new QLabel(this);
    m_timeLabel->setFixedSize(100, 20);
    m_timeLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_timeLabel->setStyleSheet(MusicUIObject::MColorStyle01);
    m_timeLabel->setGeometry(85, 37, 100, 20);

    m_downloadButton = new QPushButton(this);
    m_downloadButton->setGeometry(175, 40, 16, 16);
    m_downloadButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_downloadButton->setToolTip(tr("songDownload"));
    currentDownloadStateClicked();

    m_showMVButton = new QPushButton(this);
    m_showMVButton->setGeometry(211, 39, 16, 16);
    m_showMVButton->setStyleSheet(MusicUIObject::MKGTinyBtnMV);
    m_showMVButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_showMVButton->setToolTip(tr("showMV"));

    m_loveButton = new QPushButton(this);
    m_loveButton->setGeometry(231, 40, 16, 16);
    m_loveButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_loveButton->setToolTip(tr("bestlove"));
    currentLoveStateClicked();

    m_deleteButton = new QPushButton(this);
    m_deleteButton->setGeometry(251, 40, 16, 16);
    m_deleteButton->setStyleSheet(MusicUIObject::MKGTinyBtnDelete);
    m_deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_deleteButton->setToolTip(tr("deleteMusic"));

    m_moreButton = new QPushButton(this);
    m_moreButton->setGeometry(271, 39, 16, 16);
    m_moreButton->setStyleSheet(MusicUIObject::MPushButtonStyle13 + MusicUIObject::MKGTinyBtnMore);
    m_moreButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_moreButton->setToolTip(tr("moreFunction"));

    QMenu *menu = new QMenu(this);
    createMoreMenu(menu);
    m_moreButton->setMenu(menu);

    connect(m_loveButton, SIGNAL(clicked()), MusicApplication::instance(), SLOT(musicAddSongToLovestListAt()));
    connect(m_downloadButton, SIGNAL(clicked()), MusicLeftAreaWidget::instance(), SLOT(musicDownloadSongToLocal()));
    connect(m_deleteButton, SIGNAL(clicked()), parent, SLOT(setDeleteItemAt()));
    connect(this, SIGNAL(renameFinished(QString)), parent, SLOT(setItemRenameFinished(QString)));
    connect(this, SIGNAL(enterChanged(int,int)), parent, SLOT(listCellEntered(int,int)));
    connect(m_showMVButton, SIGNAL(clicked()), parent, SLOT(musicSongMovieFoundPy()));
    connect(addButton, SIGNAL(clicked()), parent, SLOT(musicAddToPlayLater()));

    connect(MusicLeftAreaWidget::instance(), SIGNAL(currentLoveStateChanged()), SLOT(currentLoveStateClicked()));
    connect(MusicLeftAreaWidget::instance(), SIGNAL(currentDownloadStateChanged()), SLOT(currentDownloadStateClicked()));
}

MusicSongsListPlayWidget::~MusicSongsListPlayWidget()
{
    delete m_renameLine;
    delete m_artPictureLabel;
    delete m_songNameLabel;
    delete m_timeLabel;
    delete m_loveButton;
    delete m_deleteButton;
    delete m_showMVButton;
    delete m_downloadButton;
    delete m_moreButton;
}

QString MusicSongsListPlayWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicSongsListPlayWidget::insertTimerLabel(const QString &t) const
{
    m_timeLabel->setText(t + m_totalTime);
}

void MusicSongsListPlayWidget::updateCurrentArtist()
{
    QString name = m_songNameLabel->toolTip();
    if(!showArtPicture(MusicUtils::String::artistName(name)) &&
       !showArtPicture(MusicUtils::String::songName(name)))
    {
        m_artPictureLabel->setPixmap(QPixmap(":/image/lb_defaultArt").scaled(60, 60));
    }
}

void MusicSongsListPlayWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    emit enterChanged(m_currentPlayIndex, -1);
}

void MusicSongsListPlayWidget::createMoreMenu(QMenu *menu)
{
    menu->setStyleSheet(MusicUIObject::MMenuStyle02);

    QMenu *addMenu = menu->addMenu(QIcon(":/contextMenu/btn_add"), tr("addToList"));
    addMenu->addAction(tr("musicCloud"));

    menu->addAction(QIcon(":/contextMenu/btn_mobile"), tr("songToMobile"), parent(), SLOT(musicSongTransferWidget()));
    menu->addAction(QIcon(":/contextMenu/btn_ring"), tr("ringToMobile"), parent(), SLOT(musicSongTransferWidget()));
    menu->addAction(QIcon(":/contextMenu/btn_similar"), tr("similar"), parent(), SLOT(musicSimilarFoundWidgetPy()));
    menu->addAction(QIcon(":/contextMenu/btn_share"), tr("songShare"), parent(), SLOT(musicSongSharedWidgetPy()));
    menu->addAction(QIcon(":/contextMenu/btn_kmicro"), tr("KMicro"), parent(), SLOT(musicSongKMicroWidgetPy()));
}

bool MusicSongsListPlayWidget::showArtPicture(const QString &name) const
{
    QPixmap originPath(QString(ART_DIR_FULL + name + SKN_FILE));
    if(!originPath.isNull())
    {
        m_artPictureLabel->setPixmap(originPath.scaled(60, 60));
        return true;
    }
    return false;
}

void MusicSongsListPlayWidget::setParameter(const QString &name, const QString &path)
{
    MusicSongTag tag;
    if(tag.readFile(path))
    {
        m_totalTime = "/" + tag.getLengthString();
    }
    m_songNameLabel->setText(MusicUtils::Widget::elidedText(font(), name, Qt::ElideRight, 198));
    m_songNameLabel->setToolTip(name);
    m_timeLabel->setText("00:00" + m_totalTime);

    if(!showArtPicture(MusicUtils::String::artistName(name)) &&
       !showArtPicture(MusicUtils::String::songName(name)))
    {
        m_artPictureLabel->setPixmap(QPixmap(":/image/lb_defaultArt").scaled(60, 60));
    }
}

void MusicSongsListPlayWidget::setItemRename()
{
    m_renameLine = new MusicSongsToolItemRenamedWidget(m_songNameLabel->toolTip(), this);
    connect(m_renameLine, SIGNAL(renameFinished(QString)), SLOT(setChangItemName(QString)));
    m_renameLine->setGeometry(85, 5, 200, 25);
    m_renameLine->show();
}

void MusicSongsListPlayWidget::deleteRenameItem()
{
    delete m_renameLine;
    m_renameLine = nullptr;
}

void MusicSongsListPlayWidget::setChangItemName(const QString &name)
{
    m_songNameLabel->setText(MusicUtils::Widget::elidedText(font(), name, Qt::ElideRight, 198));
    m_songNameLabel->setToolTip(name);
    emit renameFinished(name);
    QTimer::singleShot(MT_MS, this, SLOT(deleteRenameItem()));
}

void MusicSongsListPlayWidget::currentLoveStateClicked()
{
    bool state = MusicApplication::instance()->musicLovestContains();
    m_loveButton->setStyleSheet(state ? MusicUIObject::MKGTinyBtnLove : MusicUIObject::MKGTinyBtnUnLove);
}

void MusicSongsListPlayWidget::currentDownloadStateClicked()
{
    bool state = false;
    MusicApplication::instance()->musicDownloadContains(state);
    m_downloadButton->setStyleSheet(state ? MusicUIObject::MKGTinyBtnDownload : MusicUIObject::MKGTinyBtnUnDownload);
}
