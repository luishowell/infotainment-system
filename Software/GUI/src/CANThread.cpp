#include "CANThread.h"
#include <QtCore>
#include <stdio.h>
#include "Timer.h"
#include "config.h"
#include "obd2.hpp"

CANThread::CANThread()
{
    
}

void CANThread::run()
{
    printf("Starting CAN thread...\n");

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    timer.start(DIAG_RATE); //msecs

    /* init diagnostics data */
    m_msg.speed = 0;
    m_msg.rpm = 0;
    m_msg.fuel = FUEL_CAPACITY; //litres
    m_msg.connectionFault = true;

    /* OBD2 converter class */
    m_obd = new obd2();

    /* kick off the thread */
    exec();
}

/* @brief: Periodic callback method that publishes decoded CAN bus 
                        messages to the diagnostics viewer in the GUI thread */
void CANThread::PublishDiagData()
{
    printf("Publishing diag...\n");

    
    m_msg.connectionFault = !m_obd2->connected;
    m_msg.speed = m_obd2->decoded_cmd("010D");
    m_msg.rpm = m_obd2->decoded_cmd("010C");
    m_msg.intakeAirTemp = m_obd2->decoded_cmd("010F");
    m_msg.fuel = m_obd2->decoded_cmd("012F");
    

    /* dummy data */
    /*
    if (m_msg.speed < 50 )
    {
        m_msg.speed++;
    }
    else
    {
        m_msg.speed = 0;
    }
    
    if (m_msg.rpm < 30)
    {
        m_msg.rpm = m_msg.rpm + 3;
    }
    else
    {
        m_msg.rpm = 0;
    }
    
    if (m_msg.fuel > 0)
    {
        m_msg.fuel--; 
    }
    else
    {
        m_msg.fuel = 65;
    }
    m_msg.connectionFault = false;  

    */ 
    
    /* send data to the GUI's diagnostics viewer */
    emit CANPublishDiagTx(&m_msg);
}