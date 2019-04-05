/**
 * @file SensorThread.h
 * @author Jamie Brown
 * @brief Dedicated thread for interfacing with the ultrasonic parking sensors. Functionality is contained in SensorWorker and is moved to this thread.
 * @version 0.1
 * @date 2019-04-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include "config.h"

#include <QThread>

class SensorThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Sensor Thread object
     * 
     */
    explicit SensorThread();

private:
    /**
     * @brief Starts the SensorThread's executive. Actual functional implementation is done in worker classes which are moved to this thread. 
     * 
     */
    void run();
};


#endif //SENSORTHREAD_H