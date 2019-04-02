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
    /**
     * @brief Construct a new Media object
     * 
     * @param parent 
     */
    explicit Media(QWidget *parent = 0);

    /**
     * @brief 
     * 
     * @param urls 
     */
    void AddToPlaylist(const QList<QUrl> &urls);
    
    
    
public slots:
    /**
     * @brief 
     * 
     */
    void StateChangeMainMenu();

    /**
     * @brief 
     * 
     */
    void Open();

    /**
     * @brief 
     * 
     * @param duration 
     */
    void DurationChanged(int duration);

    /**
     * @brief Set the Mute object
     * 
     * @param muted 
     */
    void SetMute(bool muted);

    /**
     * @brief Set the Volume object
     * 
     * @param vol 
     */
    void SetVolume(int vol);

signals:
    /**
     * @brief 
     * 
     * @param req_state 
     * @param currentView 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private slots:
    /**
     * @brief 
     * 
     */
    void onBackClicked();

    /**
     * @brief 
     * 
     */
    void onFwdClicked();

    /**
     * @brief 
     * 
     * @param row 
     * @param cell 
     */
    void songClicked(int row, int cell);

    /**
     * @brief 
     * 
     */
    void onPlayClicked();

    /**
     * @brief 
     * 
     */
    void onRemoveClicked();

    /**
     * @brief 
     * 
     * @param secs 
     */
    void onSeekChanged(int secs);

    /**
     * @brief 
     * 
     * @param progress 
     */
    void positionChanged(qint64 progress);

    /**
     * @brief 
     * 
     * @param currentSong 
     */
    void songChanged(int currentSong);

    /**
     * @brief 
     * 
     */
    void timeout();

private:  
    /**
     * @brief Create a Layout object
     * 
     */
    void CreateLayout();

    /**
     * @brief 
     * 
     * @param url 
     */
    void AddToTable(QUrl url);

    /**
     * @brief Get the Meta Data object
     * 
     * @param metaData 
     */
    void GetMetaData(audioMetaData_t* metaData);

    /**
     * @brief Get the Album Art object
     * 
     * @param tag 
     * @return QImage 
     */
    QImage GetAlbumArt(TagLib::ID3v2::Tag *tag);

    /**
     * @brief 
     * 
     * @param index 
     */
    void ShowAlbumArt(int index);

    /**
     * @brief 
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