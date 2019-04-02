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
    /**
     * @brief Construct a new Main Menu object
     * 
     * @param parent 
     */
    explicit MainMenu(QWidget *parent = 0);
    
public slots:
    /**
     * @brief 
     * 
     */
    void StateChangeDiag();

    /**
     * @brief 
     * 
     */
    void StateChangeMedia();

    /**
     * @brief 
     * 
     */
    void StateChangeParking();

    /**
     * @brief 
     * 
     */
    void StateChangeErrorCodes();

signals:
    /**
     * @brief 
     * 
     * @param req_state 
     * @param currentView 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    /**
     * @brief Create a Layout object
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