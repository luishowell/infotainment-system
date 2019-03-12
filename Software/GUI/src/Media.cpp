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
#include <QMediaService>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QFileDialog>
#include <QStandardPaths>

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

   m_openButton = new QPushButton("Open");
   connect(m_openButton, SIGNAL(clicked()), this, SLOT(Open()));

   m_playlist = new QMediaPlaylist();
   m_player->setPlaylist(m_playlist);

   m_controls = new MediaControls(this);
   m_controls->setState(m_player->state());
   m_controls->onVolumeChanged(m_player->volume());
   m_controls->onMuteRequest(m_controls->isMuted());

   connect(m_controls, SIGNAL(playRequest()), m_player, SLOT(play()));
   connect(m_controls, SIGNAL(pauseRequest()), m_player, SLOT(pause()));
   connect(m_controls, SIGNAL(stopRequest()), m_player, SLOT(stop()));
   connect(m_controls, SIGNAL(fwdRequest()), m_playlist, SLOT(next()));
   connect(m_controls, SIGNAL(backRequest()), this, SLOT(onBackClicked()));
   connect(m_controls, SIGNAL(volumeRequest(int)), m_player, SLOT(setVolume(int)));
   connect(m_controls, SIGNAL(onMuteRequest(bool)), m_player, SLOT(setMuted()));

   connect(m_player, SIGNAL(StateChanged(QMediaPlayer::State)), m_controls, SLOT(setState(QMediaPlayer::State)));
   connect(m_player, SIGNAL(volumeRequest(int)), m_controls, SLOT(setVolume(int)));
   connect(m_player, SIGNAL(mutedRequest(bool)), m_controls, SLOT(setMuted(bool)));

   if (!m_player->isAvailable()) 
   {
        qDebug() << "MEDIA: music playernot available";
        m_controls->setEnabled(false);
        //m_playlistView->setEnabled(false);
    }

   boxLayout->addWidget(m_openButton);
   boxLayout->addWidget(m_controls);
 
   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}

void Media::AddToPlaylist(const QList<QUrl> &urls)
{
    for (auto &url: urls) 
    {
        if (IsPlaylist(url))
        {
            m_playlist->load(url);
        }
        else
        {
            m_playlist->addMedia(url);
        }
    }
}

void Media::Open()
{
   qDebug() << "MEDIA: open clicked";
   QFileDialog fileDialog(this);
   fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
   fileDialog.setWindowTitle(tr("Open Files"));
   QStringList supportedMimeTypes = m_player->supportedMimeTypes();
   if (!supportedMimeTypes.isEmpty()) 
   {
      supportedMimeTypes.append("audio/x-m3u"); // MP3 playlists
      fileDialog.setMimeTypeFilters(supportedMimeTypes);
   }
   fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
   if (fileDialog.exec() == QDialog::Accepted)
   {
      AddToPlaylist(fileDialog.selectedUrls());
   }
}

static bool IsPlaylist(const QUrl &url) // Check for ".m3u" playlists.
{
    if (!url.isLocalFile())
    {
        return false;
    }
    const QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive);
}

void Media::onBackClicked()
{
   qDebug() << "MEDIA: back button clicked";
   if(m_player->position() <= 5000)
   {
      m_playlist->previous();
   }
   else
   {
      m_player->setPosition(0);
   }
   
}
