/**
 * @file MainMenu.h
 * @author Jamie Brown
 * @brief The main widget class for the main menu. 
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

/**
 * @brief Default screen. Contains button for each screen.
 * 
 */
class MainMenu : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Main Menu object
     * 
     * @param parent 
     */
    explicit MainMenu(QWidget *parent = 0);
    
public slots:
    /**
     * @brief Emits a request to the StateManager to change to the diagnostics screen.
     * 
     */
    void StateChangeDiag();

    /**
     * @brief Emits a request to the StateManager to change to the media screen.
     * 
     */
    void StateChangeMedia();

    /**
     * @brief Emits a request to the StateManager to change to the parking screen.
     * 
     */
    void StateChangeParking();

    /**
     * @brief Emits a request to the StateManager to change to the fault codes screen.
     * 
     */
    void StateChangeErrorCodes();

signals:
    /**
     * @brief Transmits a request to change to a requested window view.
     * 
     * @param req_state The requested window. 
     * @param currentView A pointer to this QWidget, the sender.
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    /**
     * @brief Creates the buttons and lays them out. 
     * 
     */
    void CreateLayout();

    QPointer<QToolButton> m_mediaButton;
    QToolButton *m_diagButton;
    QPointer<QToolButton> m_errorButton;
    QPointer<QToolButton> m_parkButton;
    QPointer<QIcon> m_diagIcon;
    
};

#endif // MAINMENU_H