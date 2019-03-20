/**
 * @file AccWorker.h
 * @author your name (you@domain.com)
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
    explicit AccWorker();
    MMA8652FCR1* acc;

private slots:
    void Publish();
    void Work();

signals:
    void SendData(accValues_t* msg);

private:
    accValues_t* m_msg;
    //void run();
    QTimer* m_timer;
    
  
};


#endif //ACCWORKER_H