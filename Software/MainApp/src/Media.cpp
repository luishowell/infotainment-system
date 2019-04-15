/**
 * @file Media.cpp
 * @author Jamie Brown
 * @brief Implementation of Media.
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
#include <QLabel>
#include <QTime>
#include <string>
#include <algorithm>

#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/attachedpictureframe.h>
#include <taglib/tlist.h>
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>

Media::Media(QWidget *parent) : QWidget(parent) 
 {
     
    setFixedSize(widgetSize);

    CreateLayout();    

    connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));

    m_tableTimer = new QTimer(this);
    connect(m_tableTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    m_player->setVolume(0);
    
 }

void Media::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

void Media::CreateLayout()
{
   qDebug() << "MEDIA PLAYER: creating layout";

   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);
   
   QGroupBox* titleBox = new QGroupBox("Media", this);
   titleBox->setFixedSize(500, 400);
   titleBox->setAlignment(Qt::AlignHCenter);

   /* main box */
   QGridLayout* boxLayout = new QGridLayout(titleBox);
   boxLayout->setVerticalSpacing(10);

   QVBoxLayout* mainLayout = new QVBoxLayout(titleBox);

   m_player = new QMediaPlayer(this);
   m_player->setAudioRole(QAudio::MusicRole);

   for(QAudio::Role role : m_player->supportedAudioRoles())
   {
      qDebug() << "MEDIA PLAYER: supported roles  " << role;
   }

   m_openButton = new QPushButton("Load");
   m_openButton->setFixedSize(125, 50);
   connect(m_openButton, SIGNAL(clicked()), this, SLOT(Open()));

   m_removeButton = new QPushButton("Remove");
   m_removeButton->setFixedSize(125, 50);
   connect(m_removeButton, SIGNAL(clicked()), this, SLOT(onRemoveClicked()));

   m_playlist = new QMediaPlaylist();
   m_player->setPlaylist(m_playlist);

   m_playlistModel = new PlaylistModel(this);
   m_playlistModel->setPlaylist(m_playlist);

   m_controls = new MediaControls(this);
   m_controls->setState(m_player->state());
   m_controls->onVolumeChanged(m_player->volume());
   m_controls->onMuteRequest(m_controls->isMuted());

   connect(m_controls, SIGNAL(playRequest()), this, SLOT(onPlayClicked()));
   connect(m_controls, SIGNAL(pauseRequest()), m_player, SLOT(pause()));
   connect(m_controls, SIGNAL(stopRequest()), m_player, SLOT(stop()));
   connect(m_controls, SIGNAL(fwdRequest()), this, SLOT(onFwdClicked()));
   connect(m_controls, SIGNAL(backRequest()), this, SLOT(onBackClicked()));
   connect(m_controls, SIGNAL(volumeRequest(int)), this, SLOT(SetVolume(int)));
   connect(m_controls, SIGNAL(muteRequest(bool)), m_player, SLOT(setMuted(bool)));

   connect(m_player, SIGNAL(StateChanged(QMediaPlayer::State)), m_controls, SLOT(setState(QMediaPlayer::State)));
   connect(m_player, SIGNAL(volumeRequest(int)), m_controls, SLOT(setVolume(int)));
   connect(m_player, SIGNAL(mutedChanged(bool)), m_controls, SLOT(onMuteRequest(bool)));
   connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));

   connect(m_playlist, SIGNAL(currentIndexChanged(int)), this, SLOT(songChanged(int)));

   if (!m_player->isAvailable()) 
   {
        qDebug() << "MEDIA: music player not available";
        m_controls->setEnabled(false);
    }

   /* setup table */
   m_table = new QTableWidget(0, 5, this);
   m_table->setFixedSize(550, 125);
   m_table->horizontalHeader()->setStretchLastSection(true);
   m_table->setSelectionMode(QAbstractItemView::SingleSelection);
   m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
   QStringList headers;
   headers << tr("Title") << tr("Artist") << tr("Album") << tr("Genre") << tr("Year");
   m_table->setHorizontalHeaderLabels(headers);
   connect(m_table, SIGNAL(cellPressed(int,int)), this, SLOT(songClicked(int,int)));
   m_tableCount = 0;
   m_songClicked = false;
   
   m_slider = new QSlider(Qt::Horizontal, this);
   m_slider->setRange(0, m_player->duration() / 1000);
   connect(m_player, SIGNAL(durationChanged()), this, SLOT(durationChanged()));
   connect(m_slider, SIGNAL(positionChanged()), this, SLOT(positionChanged()));
   connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(onSeekChanged(int)));
   m_slider->setTracking(false);

   m_timeLabel = new QLabel(this);
   
   QPointer<QHBoxLayout> hLayout = new QHBoxLayout;
   hLayout->addWidget(m_openButton);
   hLayout->addWidget(m_removeButton);
   hLayout->addWidget(m_controls);
   
   boxLayout->addLayout(hLayout, 0, 0);
   boxLayout->addWidget(m_slider, 2, 0);
   boxLayout->addWidget(m_table, 1, 0);
   boxLayout->addWidget(m_timeLabel, 2, 1);

   /* album artwork */
   m_artHandle = new QLabel(titleBox);
   m_artHandle->setFixedSize(125, 125);
   boxLayout->addWidget(m_artHandle, 1, 1);
 
   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}

void Media::SetMute(bool muted)
{
    m_player->setMuted(m_player->isMuted());
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
         AddToTable(url);    
      }

      /* show album art if no other songs loaded */
      if (m_playlistMetaData.size() == 1) 
      {
         m_selectedSong = 0;
         ShowAlbumArt(m_selectedSong);
      }
      
   }
   
  
}

void Media::SetVolume(int vol)
{
   m_player->setMuted(false);
   m_controls->onMuteRequest(false);
   m_player->setVolume(vol);
}

void Media::AddToTable(QUrl url)
{
   audioMetaData_t metaData;
   QByteArray ba;
   
   /* convert file path to const char* */
   ba = url.path().toLocal8Bit();
   metaData.filePath = ba.data();

   GetMetaData(&metaData);
   m_playlistMetaData.push_back(metaData);

   m_table->setRowCount(m_tableCount + 1);
   m_table->setItem(m_tableCount, 0, new QTableWidgetItem(metaData.title));
   m_table->setItem(m_tableCount, 1, new QTableWidgetItem(metaData.artist));
   m_table->setItem(m_tableCount, 2, new QTableWidgetItem(metaData.album));
   m_table->setItem(m_tableCount, 3, new QTableWidgetItem(metaData.genre));
   m_table->setItem(m_tableCount, 4, new QTableWidgetItem(metaData.year));
   m_tableCount++;

   if(m_tableCount == 1) m_table->resizeColumnsToContents();
}

void Media::GetMetaData(audioMetaData_t* metaData)
{
   TagLib::String title;
   TagLib::String artist;
   TagLib::String album;
   TagLib::String genre;
   unsigned int year;
   TagLib::MPEG::File file(metaData->filePath);
   TagLib::ID3v2::Tag *tag = file.ID3v2Tag(true);

   /* get song title */
   title = tag->title();
   metaData->title = QString::fromUtf8(title.toCString());

   /* get artist name */
   artist = tag->artist();
   metaData->artist = QString::fromUtf8(artist.toCString());

   /* get album title */
   album = tag->album();
   metaData->album = QString::fromUtf8(album.toCString());

   /* get genre */
   genre = tag->genre();
   metaData->genre = QString::fromUtf8(genre.toCString());

   /* get year */
   year = tag->year();
   metaData->year = QString::number(year);

   /* get album-art */
   metaData->albumArt = GetAlbumArt(tag);

   /* get duration */
   metaData->duration = file.audioProperties()->lengthInSeconds();
}

QImage Media::GetAlbumArt(TagLib::ID3v2::Tag *tag)
{
   TagLib::ID3v2::FrameList l = tag->frameList("APIC");

    QImage image;

    if(l.isEmpty()) return image;
        
    TagLib::ID3v2::AttachedPictureFrame *f =
        static_cast<TagLib::ID3v2::AttachedPictureFrame *>(l.front());

    image.loadFromData((const uchar *) f->picture().data(), f->picture().size());

    return image;
}

void Media::ShowAlbumArt(int index)
{
   /* get the meta-data of the currently selected song */
   audioMetaData_t metaData = m_playlistMetaData[index];

   m_albumArt.convertFromImage(metaData.albumArt);
   m_albumArt = m_albumArt.scaledToWidth(125);
   m_artHandle->hide();
   m_artHandle->setPixmap(m_albumArt);
   m_artHandle->show();
}

void Media::Open()
{
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
   m_selectedSong = row;
   m_songClicked = true;
   m_tableTimer->start(5000);

}

void Media::onBackClicked()
{
   if(m_player->position() <= 5000)
   {
      if (m_playlist->currentIndex() > 0) 
      {
         m_playlist->previous();
      }
      else
      {
         m_player->setPosition(0);
      }
   }
   else
   {

      m_player->setPosition(0);
   }
   
}

void Media::onFwdClicked()
{
   if ((m_playlist->currentIndex() + 1) < m_playlistMetaData.size()) m_playlist->next();
  
}

void Media::onPlayClicked()
{
   if((m_selectedSong == m_playlist->currentIndex()) && (m_selectedSong != -1))
   {
      /* load selected song */
      m_player->stop();
      m_playlist->setCurrentIndex(m_selectedSong);
      ShowAlbumArt(m_selectedSong);
      m_player->play();
   }
   else if (m_tableCount > 0)
   {
      m_player->stop();
      m_playlist->setCurrentIndex(m_selectedSong);
      ShowAlbumArt(m_selectedSong);
      m_player->play();
   }

}

void Media::onRemoveClicked()
{   
   if (m_songClicked && (m_playlistMetaData.size() >= 0))
   {
      m_playlistMetaData.remove(m_selectedSong);
      if ( m_selectedSong > m_playlist->currentIndex() ) 
      {
         m_playlist->removeMedia(m_selectedSong);
      }
      else if ( m_playlist->currentIndex() == m_selectedSong )
      {
         m_player->stop();
         m_playlist->removeMedia(m_selectedSong);
      }
      else if ( (m_playlist->currentIndex() == -1) && (m_selectedSong == 0) )
      {
         m_player->stop();
         m_playlist->removeMedia(m_selectedSong);
      }
      m_table->removeRow(m_selectedSong);
      m_tableCount--;
      if (m_tableCount < 0) m_tableCount = 0;
      m_artHandle->hide();
   }

}

void Media::onSeekChanged(int secs)
{
   m_player->setPosition(secs * 1000);
}

void Media::DurationChanged(int duration)
{
   m_duration = duration;
   m_slider->setMaximum(m_duration);
}

void Media::positionChanged(qint64 progress)
{
   if (!m_slider->isSliderDown()) m_slider->setValue(progress / 1000);

   QString tStr;
   int seconds = progress / 1000;
   if (seconds || m_duration) 
   {
      QTime currentTime((seconds / 3600) % 60, (seconds / 60) % 60,
         seconds % 60, (seconds * 1000) % 1000);
      QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
         m_duration % 60, (m_duration * 1000) % 1000);
      QString format = "mm:ss";
      if (m_duration > 3600) format = "hh:mm:ss";
      tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
   }
    m_timeLabel->setText(tStr);

}

void Media::songChanged(int currentSong)
{
   if (!m_player->isAudioAvailable());
   if (m_playlist->currentIndex() != -1)
   {
      ShowAlbumArt(currentSong);
      SelectRow();
      DurationChanged(m_playlistMetaData[currentSong].duration);
   }
  

}

void Media::timeout()
{
   SelectRow();
}

void Media::SelectRow()
{
   m_selectedSong = m_playlist->currentIndex();
   m_table->selectRow(m_selectedSong);
}