/**
 * @file SensorWorker.cpp
 * @author Jamie Brown
 * @brief Implementation of SensorWorker
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

#define REAR_LEFT 7
#define REAR_RIGHT 3
#define FRONT_LEFT 0
#define FRONT_RIGHT 1
#define REAR_CENTRE 5
#define FRONT_CENTRE 2

using namespace std;

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
    m_msg->rearLeftConnected = false;
    m_msg->rearRightConnected = false;
    m_msg->rearCentreConnected = false;
    m_msg->frontLeftConnected = false;
    m_msg->frontCentreConnected = false;
    m_msg->frontRightConnected = false;

#endif //RPI

    /* setup periodic data publishing callback */
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(PublishSensorData()), Qt::DirectConnection);
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(PublishSensorData()));

}

void SensorWorker::Work()
{
    qDebug() << "SENSOR WORKER: started...";
    m_timer->start(100); //msecs
    while(true)
    {
#ifdef RPI
        //get the distance values from the sensor
        m_msg->frontLeftConnected = m_mux->GetDistance(FRONT_LEFT, &m_msg->frontLeft);      
        m_msg->frontRightConnected = m_mux->GetDistance(FRONT_RIGHT, &m_msg->frontRight);  
        m_msg->frontCentreConnected = m_mux->GetDistance(FRONT_CENTRE, &m_msg->frontCentre);  
        m_msg->rearLeftConnected = m_mux->GetDistance(REAR_LEFT, &m_msg->rearLeft);  
        //m_msg->rearCentreConnected = m_mux->GetDistance(REAR_CENTRE, &m_msg->rearCentre);  
        m_msg->rearRightConnected = m_mux->GetDistance(REAR_RIGHT, &m_msg->rearRight);
#else
        sleep(1);
#endif  
        
        qApp->processEvents();
    }
}

void SensorWorker::PublishSensorData()
{
#ifdef RPI
    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(m_msg);
#endif
}
