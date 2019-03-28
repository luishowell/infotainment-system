/**
 * @file MediaControls.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-03-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/* own headers */
#include "MediaControls.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>


MediaControls::MediaControls(QWidget *parent) : QWidget(parent)
{
    qDebug() << "MEDIA CONTROLS: creating...";

    m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(m_playButton, SIGNAL(clicked()), this, SLOT(onPlayClicked()));        

    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setEnabled(false);
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(onStopClicked()));        

    m_fwdButton = new QToolButton(this);
    m_fwdButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    connect(m_fwdButton, SIGNAL(clicked()), this, SLOT(onFwdClicked()));    

    m_backButton = new QToolButton(this);
    m_backButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(m_backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));    

    m_muteButton = new QToolButton(this);
    m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(m_muteButton, SIGNAL(clicked()), this, SLOT(onMuteClicked()));

    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeChanged(int)));

    /* setup the layout */
    QPointer<QBoxLayout> layout = new QHBoxLayout;
    layout->addWidget(m_backButton);
    layout->addWidget(m_playButton);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_fwdButton);
    layout->addWidget(m_muteButton);

    setLayout(layout);
}

/* public */

QMediaPlayer::State MediaControls::state() const
{
    return m_playerState;
}

void MediaControls::setState(QMediaPlayer::State state) 
{
    if (state != m_playerState)
    {
        m_playerState = state;

        switch(state)
        {
            case QMediaPlayer::StoppedState:
                m_stopButton->setEnabled(false);
                m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
            case QMediaPlayer::PlayingState:
                m_stopButton->setEnabled(true);
                m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                break;
            case QMediaPlayer::PausedState:
                m_stopButton->setEnabled(true);
                m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
        }
    }
}

int MediaControls::volume() const
{
    /* TODO: */
    /*
    qreal linearVolume = QAudio::convertVolume(m_volumeSlider->value() / qreal(100), 
                                QAudio::LogarithmicVolumeScale,
                                QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
    */
   return m_volumeSlider->value();
}


bool MediaControls::isMuted() const
{
    return m_isMuted;
}

/* PUBLIC SLOTS */
void MediaControls::onVolumeChanged(int vol)
{
    qDebug() << "MEDIA CONTROLS: volume = " << vol;

    emit volumeRequest( volume() );
}


void MediaControls::onMuteRequest(bool muted)
{
    if (muted != m_isMuted) 
    {
        m_isMuted = muted;

        m_muteButton->setIcon(style()->standardIcon(muted
                ? QStyle::SP_MediaVolumeMuted
                : QStyle::SP_MediaVolume));
    }
}

void MediaControls::stateChange(QMediaPlayer::State state)
{

}


/* PRIVATE SLOTS */

void MediaControls::onPlayClicked()
{
    qDebug() << "MEDIA CONTROLS: play clicked";

    switch(m_playerState)
    {
        case QMediaPlayer::StoppedState:
        case QMediaPlayer::PausedState:
            emit playRequest();
            break;
        case QMediaPlayer::PlayingState:
            emit pauseRequest();
            break;
    }
}

void MediaControls::onMuteClicked()
{
    qDebug() << "MEDIA CONTROLS: mute clicked";
    emit muteRequest(!m_isMuted);
}

void MediaControls::onStopClicked()
{
    qDebug() << "MEDIA CONTROLS: stop clicked";

}

void MediaControls::onBackClicked()
{
    emit backRequest();
}
