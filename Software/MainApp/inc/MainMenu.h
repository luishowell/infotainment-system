/**
 * @file MainMenu.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "types.h"

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QObject>
#include <QIcon>
#include <QPointer>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);
    
public slots:
    void StateChangeDiag();
    void StateChangeMedia();
    void StateChangeParking();
    void StateChangeErrorCodes();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPointer<QToolButton> m_mediaButton;
    QToolButton *m_diagButton;
    QPointer<QToolButton> m_errorButton;
    QPointer<QToolButton> m_parkButton;
    QPointer<QIcon> m_diagIcon;
    void CreateLayout();
};

#endif // MAINMENU_H