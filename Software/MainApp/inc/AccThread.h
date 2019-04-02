/**
 * @file AccThread.h
 * @author Jamie Brown
 * @brief Skeleton thread for obtaining accelerometer data. 
 *      Actual implementation is included in AccWorker which is moved to this thread.
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ACCTHREAD_H
#define ACCTHREAD_H

#include "config.h"
#include "types.h"

#include <QThread>
#include <string>

class AccThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Acc Thread object
     * 
     */
    explicit AccThread();
    /**
     * @brief Destroy the Acc Thread object
     * 
     */
    ~AccThread();

private:
    /**
     * @brief 
     * 
     */
    void run();
};


#endif //ACCTHREAD_H