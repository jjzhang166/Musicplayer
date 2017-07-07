#include "musicaudiorecorderwidget.h"
#include "ui_musicaudiorecorderwidget.h"
#include "musictime.h"
#include "musiccoreutils.h"
#include "musicmessagebox.h"
#include "musicaudiorecordercore.h"

#include <QMovie>
#include <QFileDialog>

MusicAudioRecorderWidget::MusicAudioRecorderWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      m_ui(new Ui::MusicAudioRecorderWidget), m_mBuffer(BufferSize, 0)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));

    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));
    m_ui->startButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    m_ui->startButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->startButton->setToolTip(tr("startAudio"));
    m_ui->stopButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    m_ui->stopButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->stopButton->setToolTip(tr("stopAudio"));
    m_ui->playButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    m_ui->playButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->playButton->setToolTip(tr("playAudio"));
    m_ui->saveButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    m_ui->saveButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->saveButton->setToolTip(tr("saveButton"));

    connect(m_ui->startButton, SIGNAL(clicked()), SLOT(onRecordStart()));
    connect(m_ui->stopButton, SIGNAL(clicked()), SLOT(onRecordStop()));
    connect(m_ui->playButton, SIGNAL(clicked()), SLOT(onRecordPlay()));
    connect(m_ui->saveButton, SIGNAL(clicked()), SLOT(onRecordSave()));

    m_ui->checkBox->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    m_ui->checkBox_2->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    m_ui->checkBox_3->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    m_ui->checkBox_4->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    m_ui->checkBox_5->setStyleSheet(MusicUIObject::MCheckBoxStyle01);
    m_ui->checkBox->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->checkBox_2->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->checkBox_3->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->checkBox_4->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->checkBox_5->setCursor(QCursor(Qt::PointingHandCursor));

    m_ui->progress->setStyleSheet(MusicUIObject::MProgressBar02);
    m_ui->horizontalSlider->setStyleSheet(MusicUIObject::MSliderStyle01);

    connect(&m_timer, SIGNAL(timeout()), SLOT(onTimerout()));
    m_ui->stopButton->setEnabled(false);
    m_ui->playButton->setEnabled(false);
    m_ui->saveButton->setEnabled(false);
    m_movie = nullptr;
    m_time = 0;

    m_miMaxValue = 0;
    m_ui->horizontalSlider->setValue(100);
    m_miVolume = 100;

    m_mpAudioInputSound = nullptr;
    m_mpAudioOutputSound = nullptr;

    m_mpInputDevSound = nullptr;
    m_mpOutputDevSound = nullptr;

    m_recordCore = new MusicAudioRecorderCore(this);

    initMonitor();
}

MusicAudioRecorderWidget::~MusicAudioRecorderWidget()
{
    delete m_recordCore;
    delete m_mpAudioInputSound;
    delete m_mpAudioOutputSound;
    delete m_mpInputDevSound;
    delete m_mpOutputDevSound;
    delete m_movie;
    delete m_ui;
}

QString MusicAudioRecorderWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicAudioRecorderWidget::onTimerout()
{
    QString text = MusicTime::normalTime2Label( ++m_time );
    m_ui->timer->setText( text );
}

void MusicAudioRecorderWidget::initMonitor()
{
    m_mFormatSound.setSampleSize(16); //set sample sze to 16 bit
    m_mFormatSound.setSampleType(QAudioFormat::UnSignedInt ); //Sample type as usigned integer sample
    m_mFormatSound.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    m_mFormatSound.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(m_mFormatSound))
    {
        //Default format not supported - trying to use nearest
        m_mFormatSound = infoIn.nearestFormat(m_mFormatSound);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(m_mFormatSound))
    {
        //Default format not supported - trying to use nearest
        m_mFormatSound = infoOut.nearestFormat(m_mFormatSound);
    }

    createAudioInput();
    createAudioOutput();

    m_mpOutputDevSound = m_mpAudioOutputSound->start();
    m_mpInputDevSound = m_mpAudioInputSound->start();
    connect(m_mpInputDevSound, SIGNAL(readyRead()), SLOT(onReadMore()));
    connect(m_ui->horizontalSlider, SIGNAL(valueChanged(int)), SLOT(onSliderValueChanged(int)));
}

void MusicAudioRecorderWidget::onRecordStart()
{
    m_recordCore->onRecordStart();
    if(m_recordCore->error())
    {
        return;
    }

    m_ui->stopButton->setEnabled(true);
    m_ui->startButton->setEnabled(false);
    m_ui->playButton->setEnabled(false);
    m_ui->saveButton->setEnabled(false);
    m_timer.start(MT_S2MS);

    if(m_movie == nullptr)
    {
        m_movie = new QMovie(":/toolSets/lb_rate", QByteArray(), this);
    }
    m_ui->timer_2->setMovie(m_movie);
    m_movie->start();
}

void MusicAudioRecorderWidget::onRecordPlay()
{
    m_recordCore->onRecordPlay();
    m_movie->start();
}

void MusicAudioRecorderWidget::onRecordStop()
{
    m_recordCore->onRecordStop();

    m_timer.stop();
    m_movie->stop();
    m_time = 0;
    m_ui->playButton->setEnabled(true);
    m_ui->startButton->setEnabled(true);
    m_ui->stopButton->setEnabled(false);
    m_ui->saveButton->setEnabled(true);
}

void MusicAudioRecorderWidget::onRecordSave()
{
    QString filename = QFileDialog::getSaveFileName( this,
        tr("choose a filename to save under"), QDir::currentPath(), "Wav(*.wav)");
    if(!filename.isEmpty())
    {
        m_recordCore->addWavHeader(MusicUtils::Core::toLocal8Bit(filename));
    }
}

void MusicAudioRecorderWidget::onStateChange(QAudio::State state)
{
    if(state == QAudio::IdleState)
    {
        onRecordStop();
    }
}

void MusicAudioRecorderWidget::createAudioInput()
{
    if (m_mpInputDevSound != nullptr)
    {
        disconnect(m_mpInputDevSound, 0, this, 0);
        m_mpInputDevSound = nullptr;
    }
    QAudioDeviceInfo inputDevice(QAudioDeviceInfo::defaultInputDevice());
    m_mpAudioInputSound = new QAudioInput(inputDevice, m_mFormatSound, this);
}

void MusicAudioRecorderWidget::createAudioOutput()
{
    QAudioDeviceInfo outputDevice(QAudioDeviceInfo::defaultOutputDevice());
    m_mpAudioOutputSound = new QAudioOutput(outputDevice, m_mFormatSound, this);
}

int MusicAudioRecorderWidget::applyVolumeToSample(short iSample)
{
    //Calculate volume, Volume limited to  max 30000 and min -30000
    return std::max(std::min(((iSample * m_miVolume) / 50), 30000), -30000);
}

void MusicAudioRecorderWidget::onSliderValueChanged(int value)
{
    m_miVolume = value;
}

void MusicAudioRecorderWidget::onReadMore()
{
    //Return if audio input is nullptr
    if(!m_mpAudioInputSound)
    {
        return;
    }
    //Check the number of samples in input buffer
    qint64 len = m_mpAudioInputSound->bytesReady();
    //Limit sample size
    if(len > 4096)
    {
        len = 4096;
    }
    //Read sound samples from input device to buffer
    qint64 l = m_mpInputDevSound->read(m_mBuffer.data(), len);
    if(l > 0)
    {
        //Assign sound samples to short array
        short* resultingData = (short*)m_mBuffer.data();
        short *outdata=resultingData;
        outdata[ 0 ] = resultingData [ 0 ];
        int iIndex;
        if(false)
        {
            //Remove noise using Low Pass filter algortm[Simple algorithm used to remove noise]
            for ( iIndex=1; iIndex < len; iIndex++ )
            {
                outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
            }
        }
        m_miMaxValue = 0;
        for ( iIndex=0; iIndex < len; iIndex++ )
        {
            //Cange volume to each integer data in a sample
            int value = applyVolumeToSample( outdata[ iIndex ]);
            outdata[ iIndex ] = value;
            m_miMaxValue = m_miMaxValue >= value ? m_miMaxValue : value;
        }
        //write modified sond sample to outputdevice for playback audio
        m_mpOutputDevSound->write((char*)outdata, len);
        QTimer::singleShot(MT_S2MS, this, SLOT(onTimeOut()));
    }
}

void MusicAudioRecorderWidget::onTimeOut()
{
    m_ui->progress->setValue(m_miMaxValue);
}

int MusicAudioRecorderWidget::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return MusicAbstractMoveDialog::exec();
}
