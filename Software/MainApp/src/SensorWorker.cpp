/**
 * @file SensorWorker.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "SensorWorker.h"
#include "Mutex.h"

#include <QtCore>
#include <iostream>
#include <unistd.h>

#define REAR_LEFT 1
#define REAR_RIGHT 2
#define FRONT_LEFT 3
#define FRONT_RIGHT 4

using namespace std;

/**
 * @brief Construct a new Sensor Worker:: Sensor Worker object
 * 
 */
SensorWorker::SensorWorker()
{  
	#ifdef RPI
    wiringPiSetup();

    sensorPins_t pins;
	pins.en = 13;
	pins.echoPin = 12;
	pins.triggerPin = 14;
	pins.sel[0] = 23;
	pins.sel[1] = 22;
	pins.sel[2] = 21;

    m_mux = new sensor_board();
    m_mux->init(pins);

    /* init sensor data */
    m_msg = new sensorDist_t;
    m_msg->frontLeft = 0;
    m_msg->frontRight = 0;
    m_msg->frontCentre = 0;
    m_msg->rearLeft = 0;
    m_msg->rearRight = 0; 
    m_msg->rearCentre = 0;
    m_msg->connectionFault = true;

#endif //RPI

    /* setup periodic data publishing callback */
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(PublishSensorData()), Qt::DirectConnection);
}

void SensorWorker::Work()
{
    m_timer->start(100); //msecs
    while(true)
    {
        qApp->processEvents();
    }
}

/**
 * @brief Periodic callback method that publishes aggregated sensor data 
                           to the diagnostics viewer in the GUI thread
 * 
 */
void SensorWorker::PublishSensorData()
{
         if ((m_mux->GetDistance(FRONT_LEFT, &m_msg->frontLeft)
         && m_mux->GetDistance(REAR_LEFT, &m_msg->rearLeft)
         && m_mux->GetDistance(FRONT_RIGHT, &m_msg->frontRight)
         && m_mux->GetDistance(REAR_RIGHT, &m_msg->rearRight))	
         == true)          
         {
             //GetDistance() was successful 
        
             m_msg->connectionFault = false;
         }
         else 
         {
             //GetDistance() failed so assume connection to sensors in lost/compromised
         //qDebug() << "Sensor connection compromised" << endl;
             m_msg->connectionFault = true;
         }
 
    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(m_msg);
//#endif
}
