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

#include <QPointer>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioProbe>

class Media : public QWidget
{
    Q_OBJECT
public:
    explicit Media(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:  
    void CreateLayout();
    QPointer<MediaControls> m_controls;
    QPointer<QPushButton> m_homeButton;
    QPointer<QMediaPlayer> m_player;
    QPointer<QMediaPlaylist> m_playlist;

};

#endif // MEDIA_H