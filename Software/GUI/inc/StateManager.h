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

#include "types.h"
#include "MainMenu.h"
#include "Diagnostics.h"
#include "Parking.h"
#include "ErrorCodes.h"
#include "Media.h"

#include <QWidget>
#include <QVector>
#include <QString>
#include <QPointer>

class StateManager : public QWidget
{
    Q_OBJECT

public:
    explicit StateManager(QWidget *parent = 0);
    QPointer<Diagnostics> m_diags;

public slots:
    void ChangeRequested(state_t req_state, QWidget* self);
    void CANPublishDiagRx(diagMsg_t* msg);
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void LogRequestRx(QVector<QString> logParams, bool start);
    void SensorPublishDiagRx(sensorDist_t* sensorData);

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);
    void DiagDataTx(diagMsg_t* msg);
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void LogRequestTx(QVector<QString> logParams, bool start);
    void SensorTx(sensorDist_t* msg);

private:
    QPointer<MainMenu> m_mainMenu;
    QPointer<Parking> m_parking;
    QPointer<ErrorCodes> m_errorCodes;
    QPointer<Media> m_media;
    
};
Q_DECLARE_METATYPE(QVector<QString>)
#endif // STATEMANAGER_H