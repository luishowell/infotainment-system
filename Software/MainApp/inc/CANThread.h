/**
 * @file CANThread.h
 * @author your name (you@domain.com)
 * @brief Dedicated thread for interfacing with the OBD2 bus. Functionality is contained in CANWorker and is moved to this thread.
 * @version 0.1
 * @date 2019-04-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CANTHREAD_H
#define CANTHREAD_H

#include "config.h"
#include "types.h"
#include "obd2.hpp"

#include <QThread>
#include <string>

/**
 * @brief Dedicated QThread for obtaining obd2 data. Actual data aquisition is in CANWorker.
 * 
 */
class CANThread : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new CANThread object
     * 
     */
    explicit CANThread();

    /**
     * @brief Destroy the CANThread object
     * 
     */
    ~CANThread();
    
private:
    /**
     * @brief Starts the CANThread's executive. Actual functional implementation is done in worker classes which are moved to this thread. 
     * 
     */
    void run();

};


#endif //CANTHREAD_H