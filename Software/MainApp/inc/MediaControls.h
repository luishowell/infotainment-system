/**
 * @file MediaControls.h
 * @author Jamie Brown
 * @brief 
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

/**
 * @brief 
 * 
 */
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
     * @brief 
     * 
     * @return QMediaPlayer::State 
     */
    QMediaPlayer::State state() const;

    /**
     * @brief Set the State object
     * 
     * @param state 
     */
    void setState(QMediaPlayer::State state);

    /**
     * @brief 
     * 
     * @return int 
     */
    int volume() const;

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isMuted() const;

public slots:
    /**
     * @brief 
     * 
     * @param vol 
     */
    void onVolumeChanged(int vol);

    /**
     * @brief 
     * 
     * @param muted 
     */
    void onMuteRequest(bool muted);

    /**
     * @brief 
     * 
     * @param state 
     */
    void stateChange(QMediaPlayer::State state);

signals:
    /**
     * @brief 
     * 
     * @param volume 
     */
    void volumeRequest(int volume);

    /**
     * @brief 
     * 
     * @param muted 
     */
    void muteRequest(bool muted);

    /**
     * @brief 
     * 
     */
    void playRequest();

    /**
     * @brief 
     * 
     */
    void pauseRequest();

    /**
     * @brief 
     * 
     */
    void stopRequest();

    /**
     * @brief 
     * 
     */
    void fwdRequest();

    /**
     * @brief 
     * 
     */
    void backRequest();

private slots:
    /**
     * @brief 
     * 
     */
    void onPlayClicked();

    /**
     * @brief 
     * 
     */
    void onMuteClicked();

    /**
     * @brief 
     * 
     */
    void onStopClicked();

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