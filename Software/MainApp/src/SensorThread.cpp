/**
 * @file SensorThread.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "SensorThread.h"
#include <QtCore>
#include <iostream>

#define REAR_LEFT 1
#define REAR_RIGHT 2
#define FRONT_LEFT 3
#define FRONT_RIGHT 4

using namespace std;

/**
 * @brief Construct a new Sensor Thread:: Sensor Thread object
 * 
 */
SensorThread::SensorThread()
{  
	
}

/**
 * @brief 
 * 
 */
void SensorThread::run()
{
    cout<<"Starting sensor thread..."<<endl;

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

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishSensorData()), Qt::DirectConnection);
    timer.start(100); //msecs 

    /* init sensor data */
    m_msg = new sensorDist_t;
    m_msg->frontLeft = 0;
    m_msg->frontRight = 0;
    m_msg->frontCentre = 0;
    m_msg->rearLeft = 0;
    m_msg->rearRight = 0; 
    m_msg->rearCentre = 0;
    m_msg->connectionFault = true;

    /* kick off the thread */
    exec();
}
                           
/**
 * @brief Periodic callback method that publishes aggregated sensor data 
                           to the diagnostics viewer in the GUI thread
 * 
 */
void SensorThread::PublishSensorData()
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
 


 /*   //testing
    float max_distance = 2.0;
    float increment_dist = 0.05;

    if (m_msg->rearLeft<max_distance)
    {        
        m_msg->frontCentre=m_msg->frontCentre+increment_dist;
        m_msg->frontLeft=m_msg->frontLeft+increment_dist;
        m_msg->frontRight= m_msg->frontRight+increment_dist;
        m_msg->rearCentre=m_msg->rearCentre+increment_dist;
        m_msg->rearLeft=m_msg->rearLeft+increment_dist;
        m_msg->rearRight=m_msg->rearRight+increment_dist;
        m_msg->connectionFault = false;      
    }  
    else
    {
        m_msg->frontCentre=0.0;
        m_msg->frontLeft=0.0;
        m_msg->frontRight=0.0;
        m_msg->rearCentre=0.0;
        m_msg->rearLeft=0.0;
        m_msg->rearRight=0.0;
        m_msg->connectionFault = false;   
    }
    //cout<<"Sensor Spawn: "<<m_msg->frontCentre<<endl;
*/

    /*
   	qDebug() << "Front left: " << m_msg->frontLeft << endl;
	qDebug() << "Front right: " << m_msg->frontRight << endl;
	qDebug() << "Rear left: " << m_msg->rearLeft << endl;
	qDebug() << "Rear right: " << m_msg->rearRight << endl;
    */

    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(m_msg);
//#endif
}

/**
 * @brief 
 * 
 */
// void SensorThread::DummyData()
// {
// #ifdef SENSOR_TEST
// 	/* dummy data */
//     m_msg->frontLeft++;
//     m_msg->frontRight++;
//     m_msg->rearLeft++;
//     m_msg->rearRight++;
//     m_msg->connectionFault = false;
// #endif
// }