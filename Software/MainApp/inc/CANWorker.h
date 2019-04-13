/**
 * @file CANWorker.h
 * @author Jamie Brown
 * @brief Contains functionality that interfaces with the OBD2 bus. This is moved to a dedicated thread, CANThread.
 * @version 0.1
 * @date 2019-04-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CANWORKER_H
#define CANWORKER_H

#include "config.h"
#include "types.h"

#ifndef GUI_TEST
#include "obd2.hpp"
#endif

#include <QGroupBox>
#include <QMetaType>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QObject>
#include <string>
#include <fstream>

/**
 * @brief Performs data aquisition from the CAN/obd2 bus. Runs in dedicated thread, CANThread.
 * 
 */
class CANWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new CANWorker object
     * 
     * @param obd 
     */
    explicit CANWorker(obd2 *obd);
    /**
     * @brief Destroy the CANWorker object
     * 
     */
    virtual ~CANWorker();
     
    QTimer *diagTimer;
    


private slots:
    /**
     * @brief Get the Diag Data object
     * 
     */
    void GetDiagData();
    /**
     * @brief 
     * 
     */
    void PublishDiagData();

    /**
     * @brief Receives a request to start logging user selected parameters.
     * 
     * @param logParams QVector of QStrings containing requested pid codes.
     * @param start Boolean indicating whether to start or stop logging.
     */
    void LogRequestRx(QVector<QString> logParams, bool start);

    /**
    * @brief Publishes diagnostics data to logger. Usually on a timer.
    * 
    */
    void PublishLogData();

    /**
     * @brief Changes the requested data from the OBD2 bus based on request.
     * 
     * @param dataRequested The requested parameter (diagParams_t).
     * @param channel The channel to assign the parameter to (obd2Channel_t).
     */
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

signals:
    /**
     * @brief Transmits diagnostics data (diagMsg_t). 
     * 
     * @param msg 
     */
    void CANPublishDiagTx(diagMsg_t* msg);
    /**
     * @brief Transmits logging data.
     * 
     */
    void CANPublishLogTx();

private:
    /**
     * @brief Fills a diagMsg_t with dummy data. Can be used to test that the diagnostics dials are working.
     * 
     */
    void DummyData();

    bool m_running;
    diagMsg_t ObdMsg;
    ofstream m_logFile;
    obd2 *m_obd;


};


#endif //CANWORKER_H
