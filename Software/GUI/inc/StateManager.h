/**
 * @file StateManager.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <QWidget>
#include <QVector>
#include <QString>
#include "types.h"
#include "MainMenu.h"
#include "Diagnostics.h"
#include "Parking.h"
#include "ErrorCodes.h"
#include "Media.h"

class StateManager : public QWidget
{
    Q_OBJECT

public:
    explicit StateManager(QWidget *parent = 0);
    Diagnostics *m_diags;

public slots:
    void ChangeRequested(state_t req_state, QWidget* self);
    void CANPublishDiagRx(diagMsg_t* msg);
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void LogRequestRx(QVector<QString> logParams);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);
    void DiagDataTx(diagMsg_t* msg);
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void LogRequestTx(QVector<QString> logParams);

private:
    MainMenu *m_mainMenu;
    
    Parking *m_parking;
    ErrorCodes *m_errorCodes;
    Media *m_media;
    
};
Q_DECLARE_METATYPE(QVector<QString>)
#endif // STATEMANAGER_H