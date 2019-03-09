/**
 * @file Media.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/* own headers */
#include "config.h"
#include "Media.h" 

#include <QDebug>
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>

/**
 * @brief Construct a new Media:: Media object
 * 
 * @param parent 
 */
Media::Media(QWidget *parent) : QWidget(parent) 
 {
     
    setFixedSize(widgetSize);

    CreateLayout();    

    connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));
    
 }

/**
 * @brief 
 * 
 */
void Media::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

/**
 * @brief 
 * 
 */
void Media::CreateLayout()
{
   qDebug() << "MEDIA PLAYER: creating layout";

   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);
   
   QGroupBox* titleBox = new QGroupBox("Media", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   /* main box */
   QGridLayout* boxLayout = new QGridLayout(titleBox);
   boxLayout->setVerticalSpacing(10);

   m_player = new QMediaPlayer(this);
   m_player->setAudioRole(QAudio::MusicRole);
   for(QAudio::Role role : m_player->supportedAudioRoles())
   {
      qDebug() << "MEDIA PLAYER:  " << role;
   }

/*
   connect(m_player, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
   connect(m_player, &QMediaPlayer::positionChanged, this, &Player::positionChanged);
   connect(m_player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &Player::metaDataChanged);
   connect(m_playlist, &QMediaPlaylist::currentIndexChanged, this, &Player::playlistPositionChanged);
   connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Player::statusChanged);
   connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &Player::bufferingProgress);
   //connect(m_player, &QMediaPlayer::videoAvailableChanged, this, &Player::videoAvailableChanged);
   connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &Player::displayErrorMessage);
   connect(m_player, &QMediaPlayer::stateChanged, this, &Player::stateChanged);
*/

   m_playlist = new QMediaPlaylist();
   m_player->setPlaylist(m_playlist);

   m_controls = new MediaControls(this);
   boxLayout->addWidget(m_controls);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}
