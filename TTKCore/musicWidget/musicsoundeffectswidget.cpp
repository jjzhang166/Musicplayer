#include "musicsoundeffectswidget.h"
#include "ui_musicsoundeffectswidget.h"
#include "musicsettingmanager.h"
#include "musicconnectionpool.h"
#include "musicuiobject.h"
#include "musicplayer.h"
///qmmp incldue
#include "effect.h"
#include "effectfactory.h"
///
#include <QBoxLayout>
#include <QStyledItemDelegate>

MusicSoundEffectsItemWidget::MusicSoundEffectsItemWidget(QWidget *parent)
    : QWidget(parent)
{
    m_type = Null;
    m_enable = false;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_textLabel = new QLabel(this);
    m_textLabel->setStyleSheet(MusicUIObject::MBackgroundStyle10);

    setText(tr("null"));

    QWidget *func = new QWidget(this);
    func->setStyleSheet(MusicUIObject::MBackgroundStyle11);
    QHBoxLayout *funcLayout = new QHBoxLayout(func);
    funcLayout->setContentsMargins(0, 5, 5, 0);
    funcLayout->setSpacing(0);

    m_settingButton = new QPushButton(func);
    m_settingButton->setStyleSheet(MusicUIObject::MBackgroundStyle01 + MusicUIObject::MBackgroundStyle01);
    m_settingButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_settingButton->setFixedWidth(40);
    m_settingButton->setText(tr("Sets"));
    m_settingButton->setEnabled(false);
    connect(m_settingButton, SIGNAL(clicked()), SLOT(soundEffectValueChanged()));

    m_openButton = new QPushButton(func);
    m_openButton->setStyleSheet(MusicUIObject::MBackgroundStyle01);
    m_openButton->setIcon(QIcon(":/tiny/btn_effect_on"));
    m_openButton->setToolTip(tr("On"));
    m_openButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_openButton->setFixedSize(16, 16);
    connect(m_openButton, SIGNAL(clicked()), SLOT(setPluginEnable()));

    QLabel *iconLabel = new QLabel(func);
    iconLabel->setStyleSheet(MusicUIObject::MBackgroundStyle01);
    iconLabel->setPixmap(QPixmap(":/tiny/lb_arrow_down_normal"));
    iconLabel->setFixedSize(16, 16);

    funcLayout->addWidget(m_settingButton);
    funcLayout->addWidget(iconLabel);
    funcLayout->addStretch(1);
    funcLayout->addWidget(m_openButton);

    layout->addWidget(m_textLabel);
    layout->addWidget(func);

    setLayout(layout);
}

MusicSoundEffectsItemWidget::~MusicSoundEffectsItemWidget()
{
    delete m_textLabel;
    delete m_openButton;
    delete m_settingButton;
}

QString MusicSoundEffectsItemWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicSoundEffectsItemWidget::setText(const QString &text)
{
    m_textLabel->setText(" " + text);
}

void MusicSoundEffectsItemWidget::setType(Type type)
{
    m_type = type;
}

void MusicSoundEffectsItemWidget::setPluginEnable(bool enable)
{
    m_enable = !enable;
    setPluginEnable();
}

bool MusicSoundEffectsItemWidget::pluginEnable() const
{
    return m_enable;
}

void MusicSoundEffectsItemWidget::setPluginEnable()
{
    if(!m_enable)
    {
        m_enable = true;
        m_openButton->setIcon(QIcon(":/tiny/btn_effect_off"));
        soundEffectCheckBoxChanged(true);
        m_settingButton->setEnabled(true);
        m_openButton->setToolTip(tr("Off"));
    }
    else
    {
        m_enable = false;
        m_openButton->setIcon(QIcon(":/tiny/btn_effect_on"));
        soundEffectCheckBoxChanged(false);
        m_settingButton->setEnabled(false);
        m_openButton->setToolTip(tr("On"));
    }
}

void MusicSoundEffectsItemWidget::soundEffectCheckBoxChanged(bool state)
{
    QString plugin( transformQStringFromEnum() );
    foreach(EffectFactory *factory, Effect::factories())
    {
        if(factory->properties().name.contains(plugin))
        {
            Effect::setEnabled(factory, state);
            break;
        }
    }
}

void MusicSoundEffectsItemWidget::soundEffectValueChanged()
{
    QString plugin( transformQStringFromEnum() );
    foreach(EffectFactory *factory, Effect::factories())
    {
        if(factory->properties().name.contains(plugin))
        {
            factory->showSettings(this);
            break;
        }
    }
}

QString MusicSoundEffectsItemWidget::transformQStringFromEnum()
{
    QString plugin;
    switch(m_type)
    {
        case BS2B:      plugin = "BS2B"; break;
        case Crossfade: plugin = "Crossfade"; break;
        case Stereo:    plugin = "Stereo"; break;
        case LADSPA:    plugin = "LADSPA"; break;
        case SoX:       plugin = "SoX"; break;
        default:        plugin = "Unknow"; break;
    }
    return plugin;
}



MusicSoundEffectsWidget::MusicSoundEffectsWidget(QWidget *parent)
    : MusicAbstractMoveDialog(parent),
      m_ui(new Ui::MusicSoundEffectsWidget)
{
    m_ui->setupUi(this);

    m_ui->topTitleCloseButton->setIcon(QIcon(":/functions/btn_close_hover"));
    m_ui->topTitleCloseButton->setStyleSheet(MusicUIObject::MToolButtonStyle03);
    m_ui->topTitleCloseButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->topTitleCloseButton->setToolTip(tr("Close"));
    connect(m_ui->topTitleCloseButton, SIGNAL(clicked()), SLOT(close()));

    m_ui->backgroundMask->setStyleSheet(QString("#backgroundMask{%1}").arg(MusicUIObject::MBackgroundStyle11));
    m_ui->volumeLeftlabel->setStyleSheet(MusicUIObject::MColorStyle06);
    m_ui->volumeRightLabel->setStyleSheet(MusicUIObject::MColorStyle06);

    m_ui->volumeSlider->setStyleSheet(MusicUIObject::MSliderStyle06);
    m_ui->volumeSlider->setRange(-100, 100);
    m_ui->volumeSlider->setValue(0);
    m_ui->volumeSlider->setToolTip("0");
    connect(m_ui->volumeSlider, SIGNAL(valueChanged(int)), SLOT(volumeSliderChanged(int)));

    m_ui->stateComboBox->setItemDelegate(new QStyledItemDelegate(m_ui->stateComboBox));
    m_ui->stateComboBox->setStyleSheet(MusicUIObject::MComboBoxStyle01 + MusicUIObject::MItemView01);
    m_ui->stateComboBox->view()->setStyleSheet(MusicUIObject::MScrollBarStyle01);
    m_ui->stateComboBox->addItems( QStringList() << tr("OperatorAll") << tr("All On") << tr("All Off"));
    connect(m_ui->stateComboBox, SIGNAL(currentIndexChanged(int)), SLOT(stateComboBoxChanged(int)));

    m_ui->eqButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);
    m_ui->eqButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->eqEffectButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_ui->eqEffectButton->setStyleSheet(MusicUIObject::MPushButtonStyle04);

    ////////////////////////////////////////////////////////////////////
    m_ui->BS2BWidget->setText("BS2B");
    m_ui->BS2BWidget->setType(MusicSoundEffectsItemWidget::BS2B);

    m_ui->CrossfadeWidget->setText("Crossfade");
    m_ui->CrossfadeWidget->setType(MusicSoundEffectsItemWidget::Crossfade);

    m_ui->StereoWidget->setText("Stereo");
    m_ui->StereoWidget->setType(MusicSoundEffectsItemWidget::Stereo);

    m_ui->SOXWidget->setText("SoX");
    m_ui->SOXWidget->setType(MusicSoundEffectsItemWidget::SoX);
#ifdef Q_OS_UNIX
    m_ui->LADSPAWidget->setText("LADSPA");
    m_ui->LADSPAWidget->setType(MusicSoundEffectsItemWidget::LADSPA);
#endif

    readSoundEffect();

    M_CONNECTION_PTR->setValue(getClassName(), this);
    M_CONNECTION_PTR->poolConnect(getClassName(), MusicPlayer::getClassName());
}

MusicSoundEffectsWidget::~MusicSoundEffectsWidget()
{
    M_CONNECTION_PTR->removeValue(getClassName());
    writeSoundEffect();

    delete m_ui;
}

QString MusicSoundEffectsWidget::getClassName()
{
    return staticMetaObject.className();
}

void MusicSoundEffectsWidget::setParentConnect(QObject *object)
{
    if(M_SETTING_PTR->value(MusicSettingManager::EqualizerEnableChoiced).toInt())
    {
        m_ui->eqButton->setText(tr("Off"));
    }
    else
    {
        m_ui->eqButton->setText(tr("On"));
    }

    m_ui->volumeSlider->setValue(M_SETTING_PTR->value(MusicSettingManager::EnhancedBalanceChoiced).toInt());

    connect(m_ui->eqButton, SIGNAL(clicked()), SLOT(equalizerButtonChanged()));
    connect(m_ui->eqEffectButton, SIGNAL(clicked()), object, SLOT(musicSetEqualizer()));
}

void MusicSoundEffectsWidget::equalizerButtonChanged(bool state)
{
    m_ui->eqButton->setText(state ? tr("Off") : tr("On"));
}

void MusicSoundEffectsWidget::equalizerButtonChanged()
{
    int state = !M_SETTING_PTR->value(MusicSettingManager::EqualizerEnableChoiced).toInt();
    equalizerButtonChanged(state);

    M_SETTING_PTR->setValue(MusicSettingManager::EqualizerEnableChoiced, state);

    emit setEqInformation();
}

void MusicSoundEffectsWidget::stateComboBoxChanged(int index)
{
    m_ui->stateComboBox->blockSignals(true);
    m_ui->stateComboBox->setCurrentIndex(0);
    m_ui->stateComboBox->blockSignals(false);

    if(index == 1)
    {
        m_ui->BS2BWidget->setPluginEnable(true);
        m_ui->CrossfadeWidget->setPluginEnable(true);
        m_ui->StereoWidget->setPluginEnable(true);
        m_ui->SOXWidget->setPluginEnable(true);
#ifdef Q_OS_UNIX
        m_ui->LADSPAWidget->setPluginEnable(true);
#endif
    }
    else if(index == 2)
    {
        m_ui->BS2BWidget->setPluginEnable(false);
        m_ui->CrossfadeWidget->setPluginEnable(false);
        m_ui->StereoWidget->setPluginEnable(false);
        m_ui->SOXWidget->setPluginEnable(false);
#ifdef Q_OS_UNIX
        m_ui->LADSPAWidget->setPluginEnable(false);
#endif
    }
}

void MusicSoundEffectsWidget::volumeSliderChanged(int value)
{
    m_ui->volumeSlider->setToolTip(QString::number(value));
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedBalanceChoiced, value);
    emit volumeChanged(value);
}

int MusicSoundEffectsWidget::exec()
{
    setBackgroundPixmap(m_ui->background, size());
    return MusicAbstractMoveDialog::exec();
}

void MusicSoundEffectsWidget::readSoundEffect()
{
    m_ui->BS2BWidget->setPluginEnable(M_SETTING_PTR->value(MusicSettingManager::EnhancedBS2BChoiced).toInt());
    m_ui->CrossfadeWidget->setPluginEnable(M_SETTING_PTR->value(MusicSettingManager::EnhancedCrossfadeChoiced).toInt());
    m_ui->StereoWidget->setPluginEnable(M_SETTING_PTR->value(MusicSettingManager::EnhancedStereoChoiced).toInt());
    m_ui->SOXWidget->setPluginEnable(M_SETTING_PTR->value(MusicSettingManager::EnhancedSOXChoiced).toInt());
#ifdef Q_OS_UNIX
    m_ui->LADSPAWidget->setPluginEnable(M_SETTING_PTR->value(MusicSettingManager::EnhancedLADSPAChoiced).toInt());
#endif
}

void MusicSoundEffectsWidget::writeSoundEffect()
{
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedBS2BChoiced, m_ui->BS2BWidget->pluginEnable());
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedCrossfadeChoiced, m_ui->CrossfadeWidget->pluginEnable());
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedSOXChoiced, m_ui->SOXWidget->pluginEnable());
#ifdef Q_OS_UNIX
    M_SETTING_PTR->setValue(MusicSettingManager::EnhancedLADSPAChoiced, m_ui->LADSPAWidget->pluginEnable());
#endif
}
