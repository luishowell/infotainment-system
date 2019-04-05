/**
 * @file MediaControls.h
 * @author Jamie Brown
 * @brief Widget containing the audio controls for the media player.
 * @version 0.1
 * @date 2019-03-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MEDIACONTROLS_H
#define MEDIACONTROLS_H

/* own headers */
#include "config.h"

#include <QPointer>
#include <QMediaPlayer>
#include <QWidget>
#include <QAbstractButton>
#include <QAbstractSlider>

class MediaControls : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Media Controls object
     * 
     * @param parent 
     */
    explicit MediaControls(QWidget *parent = 0);

    /**
     * @brief Returns the media players state.
     * 
     * @return QMediaPlayer::State State of the media player.
     */
    QMediaPlayer::State state() const;

    /**
     * @brief Set the current media player state.
     * 
     * @param state State of the media player.
     */
    void setState(QMediaPlayer::State state);

    /**
     * @brief Changes the value of the volume slider.
     * 
     * @return int Volume level.
     */
    int volume() const;

    /**
     * @brief Returns whether or not the player is muted. 
     * 
     * @return true Is muted.
     * @return false Is not muted.
     */
    bool isMuted() const;

public slots:
    /**
     * @brief Called back when the volume slider is changed, requests a volume level to the Media object.
     * 
     * @param vol Volume level.
     */
    void onVolumeChanged(int vol);

    /**
     * @brief Called back when the mute button is changed, requests a mute to the Media object.
     * 
     * @param muted To mute or unmute.
     */
    void onMuteRequest(bool muted);

signals:
    /**
     * @brief Transmits a request to a media player to change the current volume level.
     * 
     * @param volume 
     */
    void volumeRequest(int volume);

    /**
     * @brief Transmits a request to a media player to mute the audio.
     * 
     * @param muted 
     */
    void muteRequest(bool muted);

    /**
     * @brief Transmits a request to a media player to play the audio.
     * 
     */
    void playRequest();

    /**
     * @brief Transmits a request to a media player to pause the audio.
     * 
     */
    void pauseRequest();

    /**
     * @brief Transmits a request to a media player to stop the audio.
     * 
     */
    void stopRequest();

    /**
     * @brief Transmits a request to a media player to skip to the next song.
     * 
     */
    void fwdRequest();

    /**
     * @brief Transmits a request to a media player to rewind to the previous song.
     * 
     */
    void backRequest();

private slots:
    /**
     * @brief Called back when the play button clicked. Emits a play request and enables/disables relevant buttons.
     * 
     */
    void onPlayClicked();

    /**
     * @brief Called back when the mute button clicked. Emits a mute request and enables/disables relevant buttons.
     * 
     */
    void onMuteClicked();

    /**
     * @brief Called back when the stop button clicked. Emits a stop request and enables/disables relevant buttons.
     * 
     */
    void onStopClicked();

    /**
     * @brief Called back when the back button clicked. Emits a play request and enables/disables relevant buttons.
     * 
     */
    void onBackClicked();

    /**
     * @brief Called back when the skip button clicked. Emits a play request and enables/disables relevant buttons.
     * 
     */
    void onFwdClicked();

    /**
     * @brief Called back when the pause button clicked. Emits a play request and enables/disables relevant buttons.
     * 
     */
    void onPauseClicked();

private:
    QPointer<QAbstractButton> m_playButton;
    QPointer<QAbstractButton> m_pauseButton;
    QPointer<QAbstractButton> m_stopButton;
    QPointer<QAbstractButton> m_fwdButton;
    QPointer<QAbstractButton> m_backButton;
    QPointer<QAbstractButton> m_muteButton;
    QPointer<QAbstractSlider> m_volumeSlider;

    QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
    bool m_isMuted = false;
};

#endif //MEDIACONTROLS_H