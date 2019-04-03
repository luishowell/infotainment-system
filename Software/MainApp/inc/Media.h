/**
 * @file Media.h
 * @author Jamie Brown
 * @brief The main widget class for the main menu.
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
    /**
     * @brief Construct a new Media object
     * 
     * @param parent 
     */
    explicit Media(QWidget *parent = 0);

    /**
     * @brief Path to audio mp3 file. 
     * 
     * @param urls 
     */
    void AddToPlaylist(const QList<QUrl> &urls);
    
    
    
public slots:
    /**
     * @brief Emits a request to StateManager to change to the MainMenu.
     * 
     */
    void StateChangeMainMenu();

    /**
     * @brief Callback when the open button clicked. Opens file dialog window to select mp3 files. 
     * 
     */
    void Open();

    /**
     * @brief Called back when the song duration changes, changes the duration slider range to match.
     * 
     * @param duration Song duration in seconds. 
     */
    void DurationChanged(int duration);

    /**
     * @brief Mutes or un-mutes the audio.
     * 
     * @param muted Muted or not-muted. 
     */
    void SetMute(bool muted);

    /**
     * @brief Called when when a new volume requested.
     * 
     * @param vol Volume level requested. 
     */
    void SetVolume(int vol);

signals:
    /**
     * @brief Transmits a request to change to a different window.
     * 
     * @param req_state The requested window.
     * @param currentView Pointer to the current QWidget, the sender.
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private slots:
    /**
     * @brief Called back when the back arrow clicked. Either plays previous song in the playlist or restarts the current song.
     * 
     */
    void onBackClicked();

    /**
     * @brief Called back when the forward arrow clicked. Skips to the next song.
     * 
     */
    void onFwdClicked();

    /**
     * @brief Called back when a song in the playlist table is clicked. The row indicates which song has been clicked.
     * 
     * @param row 
     * @param cell 
     */
    void songClicked(int row, int cell);

    /**
     * @brief Called back when play clicked, plays either the requested song and/or unpauses the audio.
     * 
     */
    void onPlayClicked();

    /**
     * @brief Called back when remove clicked. Removes the selected song from the playlist.
     * 
     */
    void onRemoveClicked();

    /**
     * @brief Called back when the seek slider is changed, skips the audio to the time equal to the slider value in seconds.
     * 
     * @param secs 
     */
    void onSeekChanged(int secs);

    /**
     * @brief Called back when the song position is changed, changes the seek slider position and the displayed time.
     * 
     * @param progress 
     */
    void positionChanged(qint64 progress);

    /**
     * @brief Called back when the playlist changes to a new song. Shows new album art and selects the new row in the table.
     * 
     * @param currentSong 
     */
    void songChanged(int currentSong);

    /**
     * @brief Called back when the timer expires, used to highlight the currently selected song after a song has been selected but no action taken after a timeout.
     * 
     */
    void timeout();

private:  
    /**
     * @brief Create the buttons and layout.
     * 
     */
    void CreateLayout();

    /**
     * @brief Adds the meta data from an mp3 file to the playlist table.
     * 
     * @param url Path to an mp3 file.
     */
    void AddToTable(QUrl url);

    /**
     * @brief Get meta data from an mp3 file.
     * 
     * @param metaData Pointer to a structure for meta-data, must contain the path to the file.
     */
    void GetMetaData(audioMetaData_t* metaData);

    /**
     * @brief Gets the album art from the meta data and converts to a Qt object.
     * 
     * @param tag An ID3v2 tag for an mp3 file.
     * @return QImage The converted album art from the meta data.
     */
    QImage GetAlbumArt(TagLib::ID3v2::Tag *tag);

    /**
     * @brief Show the album art for a song in the playlist.
     * 
     * @param index The index of the requested song in the playlist. 
     */
    void ShowAlbumArt(int index);

    /**
     * @brief Selects the row of the currently playing song.
     * 
     */
    void SelectRow();
    
    int m_tableCount;
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