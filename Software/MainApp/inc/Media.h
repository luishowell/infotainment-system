/**
 * @file Media.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MEDIA_H
#define MEDIA_H

/* own headers */
#include "types.h"
#include "MediaControls.h"
#include "PlaylistModel.h"

#include <QPointer>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioProbe>
#include <QTableWidget>
#include <QUrl>
#include <QImage>
#include <QLabel>
#include <QTimer>

#include <taglib/tag.h>
#include <id3v2frame.h>


class Media : public QWidget
{
    Q_OBJECT
public:
    explicit Media(QWidget *parent = 0);

    void AddToPlaylist(const QList<QUrl> &urls);
    
    
    
public slots:
    void StateChangeMainMenu();
    void Open();
    void DurationChanged(int duration);
    void SetMute(bool muted);
    void SetVolume(int vol);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private slots:
    void onBackClicked();
    void onFwdClicked();
    void songClicked(int row, int cell);
    void onPlayClicked();
    void onRemoveClicked();
    void onSeekChanged(int secs);
    void positionChanged(qint64 progress);
    void songChanged(int currentSong);
    void timeout();

private:  
    void CreateLayout();
    void AddToTable(QUrl url);
    int m_tableCount;
    void GetMetaData(audioMetaData_t* metaData);
    QImage GetAlbumArt(TagLib::ID3v2::Tag *tag);
    void ShowAlbumArt(int index);
    void SelectRow();
    
    
    QPointer<QLabel> m_artHandle;
    QPointer<QLabel> m_timeLabel;
    QVector<audioMetaData_t> m_playlistMetaData;
    QPointer<PlaylistModel> m_playlistModel;
    QPointer<QTableWidget> m_table;
    QPointer<MediaControls> m_controls;
    QPointer<QPushButton> m_homeButton;
    QPointer<QMediaPlayer> m_player;
    QPointer<QMediaPlaylist> m_playlist;
    QPointer<QPushButton> m_openButton;
    QPointer<QPushButton> m_removeButton;
    QPointer<QSlider> m_slider;
    QPointer<QTimer> m_tableTimer;

    QPixmap m_albumArt;
    int m_selectedSong = 0;
    bool m_songClicked = false;
    qint64 m_duration = 0;

};

static bool IsPlaylist(const QUrl &url);
#endif // MEDIA_H