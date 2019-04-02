/**
 * @file SensorWorker.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-04-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef SENSORWORKER_H
#define SENSORWORKER_H

#include "config.h"

#include "types.h"
#include "sensor_board.h"

#include <QObject>
#include <QTimer>

class SensorWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Sensor Worker object
     * 
     */
    explicit SensorWorker();
    
private slots:
    /**
     * @brief 
     * 
     */
    void PublishSensorData();

    /**
     * @brief 
     * 
     */
    void Work();

signals:
    /**
     * @brief 
     * 
     * @param msg 
     */
    void SensorPublishDiagTx(sensorDist_t* msg);

private:
    /**
     * @brief 
     * 
     */
    void DummyData();

    sensorDist_t* m_msg;
    QTimer* m_timer;
    sensor_board* m_mux;
  
};


#endif //SENSORTHREAD_H