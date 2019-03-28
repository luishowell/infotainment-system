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
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMediaService>
#include <QAudioProbe>
#include <QMediaMetaData>
#include <QFileDialog>
#include <QStandardPaths>
#include <QHeaderView>
#include <string>
#include <algorithm>

#include <taglib/tag.h>
#include <fileref.h>

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

   QVBoxLayout* mainLayout = new QVBoxLayout(titleBox);

   m_player = new QMediaPlayer(this);
   m_player->setAudioRole(QAudio::MusicRole);

   //qDebug() << "MEDIA PLAYER: supported roles  " << role;
   for(QAudio::Role role : m_player->supportedAudioRoles())
   {
      qDebug() << "MEDIA PLAYER: supported roles  " << role;
   }

   m_openButton = new QPushButton("Open");
   connect(m_openButton, SIGNAL(clicked()), this, SLOT(Open()));

   m_playlist = new QMediaPlaylist();
   m_player->setPlaylist(m_playlist);

   m_playlistModel = new PlaylistModel(this);
   m_playlistModel->setPlaylist(m_playlist);

   m_controls = new MediaControls(this);
   m_controls->setState(m_player->state());
   m_controls->onVolumeChanged(m_player->volume());
   m_controls->onMuteRequest(m_controls->isMuted());

   //connect(m_controls, SIGNAL(playRequest()), m_player, SLOT(play()));
   connect(m_controls, SIGNAL(playRequest()), this, SLOT(onPlayClicked()));
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
        qDebug() << "MEDIA: music player not available";
        m_controls->setEnabled(false);
        //m_playlistView->setEnabled(false);
    }


   /* setup table */
   m_table = new QTableWidget(0, 5, this);
   m_table->horizontalHeader()->setStretchLastSection(true);
   m_table->setSelectionMode(QAbstractItemView::SingleSelection);
   //m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
   m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
   QStringList headers;
   headers << tr("Title") << tr("Artist") << tr("Album") << tr("Genre") << tr("Year");
   m_table->setHorizontalHeaderLabels(headers);
   connect(m_table, SIGNAL(cellPressed(int,int)), this, SLOT(songClicked(int,int)));
   m_tableCount = 0;
   

   QPointer<QHBoxLayout> hLayout = new QHBoxLayout;
   hLayout->addWidget(m_openButton);
   hLayout->addWidget(m_controls);

   //mainLayout->addLayout(hLayout);
   //mainLayout->addWidget(m_table);

   boxLayout->addWidget(m_openButton);
   boxLayout->addWidget(m_controls);
   boxLayout->addWidget(m_table);

 
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
         AddToTable(url);
      }
      else
      {
         m_playlist->addMedia(url);
         AddToTable(url);
             
      }
      
}
  
}

void Media::AddToTable(QUrl url)
{
   audioMetaData_t metaData;
   const char* filePath;
   QByteArray ba;
   
   /* convert file path to const char* */
   ba = url.path().toLocal8Bit();
   filePath = ba.data();

   GetMetaData(filePath, &metaData);

   m_table->setRowCount(m_tableCount + 1);
   m_table->setItem(m_tableCount, 0, new QTableWidgetItem(metaData.title));
   m_table->setItem(m_tableCount, 1, new QTableWidgetItem(metaData.artist));
   m_table->setItem(m_tableCount, 2, new QTableWidgetItem(metaData.album));
   m_table->setItem(m_tableCount, 3, new QTableWidgetItem(metaData.genre));
   m_table->setItem(m_tableCount, 4, new QTableWidgetItem(metaData.year));
   m_tableCount++;
}

void Media::GetMetaData(const char* filePath, audioMetaData_t* metaData)
{
   TagLib::String title;
   TagLib::String artist;
   TagLib::String album;
   TagLib::String genre;
   unsigned int year;
   TagLib::FileRef f(filePath);

   /* get song title */
   title = f.tag()->title();
   metaData->title = QString::fromUtf8(title.toCString());

   /* get artist name */
   artist = f.tag()->artist();
   metaData->artist = QString::fromUtf8(artist.toCString());

   /* get album title */
   album = f.tag()->album();
   metaData->album = QString::fromUtf8(album.toCString());

   /* get genre */
   genre = f.tag()->genre();
   metaData->genre = QString::fromUtf8(genre.toCString());

   /* get year */
   year = f.tag()->year();
   metaData->year = QString::number(year);
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

void Media::songClicked(int row, int cell)
{
   qDebug() << "MEDIA: song clicked (row " << row << ", cell " << cell << ")";
   m_selectedSong = row;

   //GetMetaData(m_player, row);
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

void Media::onPlayClicked()
{
   qDebug() << "MEDIA: play clicked";
   //qDebug() << m_playlist->media(0).canonicalUrl().fileName();

   /* load selected song */
   m_player->stop();
   m_playlist->setCurrentIndex(m_selectedSong);
   m_player->play();


}
