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

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include "types.h"

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
    QPushButton *m_homeButton;
    void CreateLayout();
};

#endif // MEDIA_H