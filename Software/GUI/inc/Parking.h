/**
 * @file Parking.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PARKING_H
#define PARKING_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include "types.h"

class Parking : public QWidget
{
    Q_OBJECT
public:
    explicit Parking(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_homeButton;
    void CreateLayout ();
};

#endif // PARKING_H