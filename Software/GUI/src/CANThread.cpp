#include "CANThread.h"
#include <QtCore>
#include <stdio.h>
#include "Timer.h"


CANThread::CANThread()
{
    
}

void CANThread::run()
{
    printf("Starting CAN thread...\n");

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    timer.start(1000); //msecs

    /* init diagnostics data */
    m_msg.speed = 0;
    m_msg.rpm = 0;
    m_msg.fuel = 65; //litres
    m_msg.connectionFault = true;

    /* kick off the thread */
    exec();
}

/* @brief: Periodic callback method that publishes decoded CAN bus 
                        messages to the diagnostics viewer in the GUI thread */
void CANThread::PublishDiagData()
{
    printf("Publishing diag...\n");

    /* dummy data */
    m_msg.speed++;
    m_msg.rpm = m_msg.rpm + 2;
    m_msg.fuel--; 
    m_msg.connectionFault = false;

    /* send data to the GUI's diagnostics viewer */
    emit CANPublishDiagTx(&m_msg);
}