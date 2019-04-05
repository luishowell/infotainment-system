/**
 * @file StateManager.h
 * @author Jamie Brown
 * @brief Class that handles state change requests to change windows within the touchscreen GUI.
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
     * @param parent Parent QWidget of this object.
     * @param myObd Pointer to an obd2 bus object.
     * @param acc Pointer to a MMA8652FCR1 accelerometer object.
     */
    explicit StateManager(QWidget *parent = 0, obd2* myObd = 0, MMA8652FCR1* acc = 0);
    QPointer<Diagnostics> m_diags;

public slots:
    /**
     * @brief State machine that determines the currently displayed view/menu.
     * 
     * @param req_state The requested window to change to an as enum.
     * @param self Pointer to the sender widget. 
     */
    void ChangeRequested(state_t req_state, QWidget* self);

    /**
     * @brief Receiving callback of diagnostics data from the CAN thread. Simply forwards the data on to Diagnostics.
     * 
     * @param msg Structure containing the diagnostics data.
     */
    void CANPublishDiagRx(diagMsg_t* msg);

    /**
     * @brief Called back when a new OBD2 channel is requested. Simply forwards the request to the CANWorker running in the CANThread.
     * 
     * @param dataRequested Structure of the requested OBD2 data.
     * @param channel Requested channel (A or B).
     */
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

    /**
     * @brief Called back when a data log request received from the diagnostics screen. Simply forwards the request to the CANWorker/CANThread.
     * 
     * @param logParams A list of requested parameters as pid codes.
     * @param start Boolean indicating whether to start or stop logging.
     */
    void LogRequestRx(QVector<QString> logParams, bool start);

    /**
     * @brief Called back when sensor data received from the SensorWorker/SensorThread. Simply forwards to the parking-mode screen.
     * 
     * @param sensorData Pointer to a structure containing the sensor data.
     */
    void SensorPublishDiagRx(sensorDist_t* sensorData);

    /**
     * @brief Called back when accelerometer data received from AccWorker/AccThread. Simply forwards to the diagnostics screen.
     * 
     * @param msg Pointer to structure containing the accelerometer data.
     */
    void AccDataRx(accValues_t* msg);

signals:
    /**
     * @brief Transmits a request to change to a different GUI view. 
     * 
     * @param req_state The requested GUI view as an enum.
     * @param currentView Pointer to the sender QWidget.
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

    /**
     * @brief Transmits diagnostics information.
     * 
     * @param msg Pointer to structure of diagnostics data.
     */
    void DiagDataTx(diagMsg_t* msg);

    /**
     * @brief Transmits a request to change the data obtained for a given OBD2 channel.
     * 
     * @param dataRequested Parameter to be obtained.
     * @param channel OBD2 channel number (A or B).
     */
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

    /**
     * @brief Transmits a data log request.
     * 
     * @param logParams List of requested parameters as pid codes. 
     * @param start Boolean indicating whether to start or stop logging.
     */
    void LogRequestTx(QVector<QString> logParams, bool start);

    /**
     * @brief Transmits parking sensor data.
     * 
     * @param msg Pointer to structure of sensor data.
     */
    void SensorTx(sensorDist_t* msg);

    /**
     * @brief Transmits accelerometer data.
     * 
     * @param msg Pointer to structure of accelerometer data.
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