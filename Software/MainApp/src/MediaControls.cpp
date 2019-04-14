/**
 * @file MediaControls.cpp
 * @author Jamie Brown
 * @brief Implementation of MediaControls.
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

    QSize btnSize(50, 50);

    m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    m_playButton->setFixedSize(btnSize);
    connect(m_playButton, SIGNAL(clicked()), this, SLOT(onPlayClicked())); 

    m_pauseButton = new QToolButton(this);
    m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause)); 
    m_pauseButton->setFixedSize(btnSize);
    m_pauseButton->setEnabled(false);
    connect(m_pauseButton, SIGNAL(clicked()), this, SLOT(onPauseClicked())); 
    
    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setFixedSize(btnSize);
    m_stopButton->setEnabled(false);
    connect(m_stopButton, SIGNAL(clicked()), this, SLOT(onStopClicked()));        

    m_fwdButton = new QToolButton(this);
    m_fwdButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    m_fwdButton->setFixedSize(btnSize);
    connect(m_fwdButton, SIGNAL(clicked()), this, SLOT(onFwdClicked()));    

    m_backButton = new QToolButton(this);
    m_backButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    m_backButton->setFixedSize(btnSize);
    connect(m_backButton, SIGNAL(clicked()), this, SLOT(onBackClicked()));    

    m_muteButton = new QToolButton(this);
    m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    m_muteButton->setFixedSize(btnSize);
    connect(m_muteButton, SIGNAL(clicked()), this, SLOT(onMuteClicked()));

    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onVolumeChanged(int)));

    /* setup the layout */
    QPointer<QBoxLayout> layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(m_backButton);
    layoutButtons->addWidget(m_playButton);
    layoutButtons->addWidget(m_pauseButton);
    layoutButtons->addWidget(m_stopButton);
    layoutButtons->addWidget(m_fwdButton);
    layoutButtons->addWidget(m_muteButton);

    QPointer<QBoxLayout> vLayout = new QVBoxLayout;
    vLayout->addLayout(layoutButtons);
    vLayout->addWidget(m_volumeSlider);

    setLayout(vLayout);

    
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



/* PRIVATE SLOTS */

void MediaControls::onPlayClicked()
{
    qDebug() << "MEDIA CONTROLS: play clicked";

   emit playRequest();
   m_pauseButton->setEnabled(true);
   m_stopButton->setEnabled(false);
}

void MediaControls::onPauseClicked()
{
    qDebug() << "MEDIA CONTROLS: pause clicked";
    emit pauseRequest();
    m_pauseButton->setEnabled(false);
    m_playButton->setEnabled(true);
    m_stopButton->setEnabled(true);
}

void MediaControls::onMuteClicked()
{
    qDebug() << "MEDIA CONTROLS: mute clicked";
    emit muteRequest(!m_isMuted);
}

void MediaControls::onStopClicked()
{
    qDebug() << "MEDIA CONTROLS: stop clicked";
    emit stopRequest();

}

void MediaControls::onBackClicked()
{
    emit backRequest();
}

void MediaControls:: onFwdClicked()
{
    emit fwdRequest();
}