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
    explicit MediaControls(QWidget *parent = 0);

    QMediaPlayer::State state() const;
    void setState(QMediaPlayer::State state);
    int volume() const;
    bool isMuted() const;
    //qreal playbackRate() const;

public slots:
    void onVolumeChanged(int vol);
    void onMuteRequest(bool muted);
    void stateChange(QMediaPlayer::State state);

signals:
    void volumeRequest(int volume);
    void muteRequest(bool muted);
    void playRequest();
    void pauseRequest();
    void stopRequest();
    void fwdRequest();
    void backRequest();

private slots:
    void onPlayClicked();
    void onMuteClicked();
    void onStopClicked();
    void onBackClicked();
    void onFwdClicked();
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