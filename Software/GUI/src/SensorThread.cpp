#include "SensorThread.h"
#include <QtCore>
#include <iostream>
//#include <stdio.h>
#include "Timer.h"
#include <wiringPi.h>

#define REAR_LEFT 5
#define REAR_RIGHT 7
#define FRONT_LEFT 4
#define FRONT_RIGHT 6
//#define SENSOR_TEST 1

using namespace std;

SensorThread::SensorThread()
{  
	
}

void SensorThread::run()
{
    cout<<"Starting sensor thread..fhershy."<<endl;


	wiringPiSetup();

    sensorPins_t pins;
	pins.en = 3;
	pins.echoPin = 2;
	pins.triggerPin = 0;
	pins.sel[0] = 12;
	pins.sel[1] = 13;
	pins.sel[2] = 14;

    m_mux = new sensor_board();

    m_mux->init(pins);

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishSensorData()), Qt::DirectConnection);
    timer.start(1000); //msecs dsfghtdhtruh

    /* init sensor data */
    m_msg = new sensorDist_t;
    m_msg->frontLeft = 0;
    m_msg->frontRight = 0;
    m_msg->rearLeft = 0;
    m_msg->rearRight = 0; 
    m_msg->connectionFault = true;

    /* kick off the thread */
    exec();

}

/* @brief: Periodic callback method that publishes aggregated sensor data 
                           to the diagnostics viewer in the GUI thread */
void SensorThread::PublishSensorData()
{
cout << "FIRE!" << endl;
//#ifdef SENSOR_TEST
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
	qDebug() << "Sensor connection compromised" << endl;
        m_msg->connectionFault = true;
    }
    
   	qDebug() << "Front left: " << m_msg->frontLeft << endl;
	qDebug() << "Front right: " << m_msg->frontRight << endl;
	qDebug() << "Rear left: " << m_msg->rearLeft << endl;
	qDebug() << "Rear right: " << m_msg->rearRight << endl;

    /* send data to the GUI's diagnostics viewer */
    emit SensorPublishDiagTx(m_msg);
//#endif
}

void SensorThread::DummyData()
{
#ifdef SENSOR_TEST
	/* dummy data */
    m_msg->frontLeft++;
    m_msg->frontRight++;
    m_msg->rearLeft++;
    m_msg->rearRight++;
    m_msg->connectionFault = false;
#endif
}
