#include "SensorThread.h"
#include <QtCore>
#include <iostream>
//#include <stdio.h>
#include "Timer.h"

using namespace std;

SensorThread::SensorThread()
{  

}

void SensorThread::run()
{
    cout<<"Starting sensor thread..."<<endl;

    /*
    m_frontLeft = new UltrasonicSensor();
    m_frontRight = new UltrasonicSensor();
    m_rearLeft = new UltrasonicSensor();
    m_rearRight = new UltrasonicSensor();

    //init with placeholder pins
    m_frontLeft.init(pinA, pinB);
    m_frontRight.init(pinC, pinD);
    m_rearLeft.init(pinE, pinF);
    m_leftRight.init(pinG, pinH);
    */

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    timer.start(1000); //msecs

    /* init sensor data */
    m_msg.frontLeft = NULL;
    m_msg.frontRight = NULL;
    m_msg.rearLeft = NULL;
    m_msg.rearRight = NULL; 
    m_msg.connectionFault = true;

    /* kick off the thread */
    exec();
}

/* @brief: Periodic callback method that publishes aggregated sensor data 
                           to the diagnostics viewer in the GUI thread */
void SensorThread::PublishSensorData()
{
    /* 
    //assuming GetDistance() takes a pointer to a double and returns a status flag
    if ((m_frontLeft->GetDistance(&m_msg.frontLeft) && m_frontRight->GetDistance(&m_msg.frontRight) 
        &&  m_rearLeft.GetDistance(&m_msg.rearLeft)  && m_rearRight.GetDistance(&m_msg.rearRight) )   
        == true)
    {
        //GetDistance() was successful 
        m_msg->connectionFault = false;
    }
    else 
    {
        //GetDistance() failed so assume connection to sensors in lost/compromised
        m_msg->connectionFault = true;
    }
    */
    

    /* dummy data */
    m_msg.frontLeft++;
    m_msg.frontRight++;
    m_msg.rearLeft++;
    m_msg.rearRight++;
    m_msg.connectionFault = false;

    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(&m_msg);
}