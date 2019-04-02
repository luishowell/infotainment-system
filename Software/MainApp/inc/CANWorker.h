/**
 * @file CANWorker.h
 * @author Jamie Brown
 * @brief 
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
     * @brief 
     * 
     * @param logParams 
     * @param start 
     */
    void LogRequestRx(QVector<QString> logParams, bool start);
    /**
     * @brief 
     * 
     */
    void PublishLogData();
    /**
     * @brief 
     * 
     * @param dataRequested 
     * @param channel 
     */
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

signals:
    /**
     * @brief 
     * 
     * @param msg 
     */
    void CANPublishDiagTx(diagMsg_t* msg);
    /**
     * @brief 
     * 
     */
    void CANPublishLogTx();

private:
    /**
     * @brief Get the Log Data object
     * 
     */
    void GetLogData();
    /**
     * @brief 
     * 
     */
    void DummyData();

    bool m_running;
    diagMsg_t ObdMsg;
    ofstream m_logFile;
    obd2 *m_obd;


};


#endif //CANWORKER_H
