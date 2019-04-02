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
#include "AccGauge.h"
#include "MMA8652FCR1.h"

#include <QWidget>
#include <QVector>
#include <QString>
#include <QPointer>

class StateManager : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new State Manager object
     * 
     * @param parent 
     * @param myObd 
     * @param acc 
     */
    explicit StateManager(QWidget *parent = 0, obd2* myObd = 0, MMA8652FCR1* acc = 0);
    QPointer<Diagnostics> m_diags;

public slots:
    /**
     * @brief 
     * 
     * @param req_state 
     * @param self 
     */
    void ChangeRequested(state_t req_state, QWidget* self);

    /**
     * @brief 
     * 
     * @param msg 
     */
    void CANPublishDiagRx(diagMsg_t* msg);

    /**
     * @brief 
     * 
     * @param dataRequested 
     * @param channel 
     */
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

    /**
     * @brief 
     * 
     * @param logParams 
     * @param start 
     */
    void LogRequestRx(QVector<QString> logParams, bool start);

    /**
     * @brief 
     * 
     * @param sensorData 
     */
    void SensorPublishDiagRx(sensorDist_t* sensorData);

    /**
     * @brief 
     * 
     * @param msg 
     */
    void AccDataRx(accValues_t* msg);

signals:
    /**
     * @brief 
     * 
     * @param req_state 
     * @param currentView 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

    /**
     * @brief 
     * 
     * @param msg 
     */
    void DiagDataTx(diagMsg_t* msg);

    /**
     * @brief 
     * 
     * @param dataRequested 
     * @param channel 
     */
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

    /**
     * @brief 
     * 
     * @param logParams 
     * @param start 
     */
    void LogRequestTx(QVector<QString> logParams, bool start);

    /**
     * @brief 
     * 
     * @param msg 
     */
    void SensorTx(sensorDist_t* msg);

    /**
     * @brief 
     * 
     * @param msg 
     */
    void AccDataTx(accValues_t* msg);

private:
    obd2* m_obd;
    QPointer<MainMenu> m_mainMenu;
    QPointer<Parking> m_parking;
    QPointer<ErrorCodes> m_errorCodes;
    QPointer<Media> m_media;
    
};
Q_DECLARE_METATYPE(QVector<QString>)
#endif // STATEMANAGER_H