/**
 * @file AccWorker.cpp
 * @author your name (you@domain.com)
 * @brief Implementation of AccWorker.
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define IRQ_PIN1 7
#define IRQ_PIN2 0
#define DEV_ID 0x1D

#include "AccWorker.h"

#include <QtCore>
#include <time.h>
#ifdef RPI
#include <wiringPi.h>
#endif

AccWorker::AccWorker()
{
    acc = new MMA8652FCR1;
    acc->init(DEV_ID, IRQ_PIN1, IRQ_PIN2);

    m_msg = new accValues_t;

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(Publish()));

}

void AccWorker::Work()
{
    double timeoutLength = 20000;
    double timeLeft;
    time_t whileStart;
    time_t whileEnd;
    time_t timeTaken;

    /* start publishing timer */
    m_timer->start(250);

    while(true)
    {
        timeLeft = timeoutLength;
 #ifdef RPI       
        whileStart = micros();
        while( (digitalRead(IRQ_PIN1) == LOW) && (timeLeft > 0) ) 
        {
            whileEnd = micros();
            timeTaken = whileEnd - whileStart;
            timeLeft = timeoutLength - timeTaken;
            if (timeTaken < 0)
            {
                /* timed out */
            }
            else
            {
                /* triggered by IRQ */
            }
            acc->getData(m_msg);
            qDebug () << "ACC WORKER: x-data = " << m_msg->xAxis;
            
        }
#endif
        qApp->processEvents();

    }
}

void AccWorker::Publish()
{
    qDebug() << "ACC WORKER: send!";

    /* send */
    emit SendData(m_msg);



    
}
