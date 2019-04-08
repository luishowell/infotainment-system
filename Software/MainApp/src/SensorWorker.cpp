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

#define REAR_LEFT 0
#define REAR_RIGHT 1
#define FRONT_LEFT 2
#define FRONT_RIGHT 3
//#define REAR_CENTRE 4
//#define FRONT_CENTRE 5

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
    m_msg->rearLeftConnectionFault = true;
    m_msg->rearRightConnectionFault = true;
    m_msg->rearCentreConnectionFault = true;
    m_msg->frontLeftConnectionFault = true;
    m_msg->frontCentreConnectionFault = true;
    m_msg->frontRightConnectionFault = true;

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
        qDebug() << "SENSOR WORKER: getting data";
#ifdef RPI
        //get the distance values from the sensor
        m_msg->frontLeftConnectionFault = m_mux->GetDistance(FRONT_LEFT, &m_msg->frontLeft);      
        m_msg->frontRightConnectionFault = m_mux->GetDistance(FRONT_RIGHT, &m_msg->frontRight);  
        //m_msg->frontCentreConnectionFault = m_mux->GetDistance(FRONT_CENTRE, &m_msg->frontCentre);  
        m_msg->rearLeftConnectionFault = m_mux->GetDistance(REAR_LEFT, &m_msg->rearLeft);  
        //m_msg->rearCentreConnectionFault = m_mux->GetDistance(REAR_CENTRE, &m_msg->rearCentre);  
        m_msg->rearRightConnectionFault = m_mux->GetDistance(REAR_RIGHT, &m_msg->rearRight); 
#else
        sleep(1);
#endif  
        
        qApp->processEvents();
    }
}

void SensorWorker::PublishSensorData()
{
    qDebug() << "SENSOR WORKER: publishing";
#ifdef RPI

    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(m_msg);
#endif
}
