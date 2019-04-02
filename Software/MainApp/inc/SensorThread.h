/**
 * @file SensorThread.h
 * @author Jamie Brown
 * @brief 
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
     * @brief 
     * 
     */
    void run();
};


#endif //SENSORTHREAD_H