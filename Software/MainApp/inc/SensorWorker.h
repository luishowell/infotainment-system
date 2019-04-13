/**
 * @file SensorWorker.h
 * @author Jamie Brown
 * @brief Contains functionality that interfaces with the ultrasonic parking sensors. This is moved to a dedicated thread, SensorThread.
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

/**
 * @brief Performs data aquisition with an ultrasonic sensor. Runs in dedicated thread, SensorThread.
 * 
 */
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
    * @brief Periodic callback method that publishes aggregated sensor data 
                           to the diagnostics viewer in the GUI thread.
     */
    void PublishSensorData();

    /**
     * @brief Requests sensor data from the interface. 
     * 
     */
    void Work();

signals:
    /**
     * @brief Transmits the aggregated sensor data to the parking mode GUI.
     * 
     * @param msg 
     */
    void SensorPublishDiagTx(sensorDist_t* msg);

private:
    /**
     * @brief Fill the sensor data structure with dummy values. Can be used to test the parking mode GUI.
     * 
     */
    void DummyData();

    sensorDist_t* m_msg;
    QTimer* m_timer;
    sensor_board* m_mux;
  
};


#endif //SENSORTHREAD_H