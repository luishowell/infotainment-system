/**
 * @file AccWorker.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ACCWORKER_H
#define ACCWORKER_H

#include "config.h"
#include "types.h"
#include "MMA8652FCR1.h"

#include <QObject>
#include <QTimer>

class AccWorker : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Acc Worker object
     * 
     */
    explicit AccWorker();
    
    MMA8652FCR1* acc;

private slots:
    /**
     * @brief Timer callback, sends accelerometer data using a signal. 
     * 
     */
    void Publish();

    /**
     * @brief Obtains accelerometer data in an infinite loop. Actual transmission of data is done in Publish() on a timer.
     * 
     */
    void Work();

signals:
    /**
     * @brief 
     * 
     * @param msg A pointer to struct of accelerometer values (accValues_t).
     */
    void SendData(accValues_t* msg);

private:
    accValues_t* m_msg;
    QTimer* m_timer;
    
  
};


#endif //ACCWORKER_H