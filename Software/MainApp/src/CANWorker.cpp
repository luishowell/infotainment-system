/**
 * @file CANWorker.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CANWorker.h"
#include <QtCore>
#include <iostream>
#include <unistd.h>
#include <QThread>

using namespace std;

#ifndef GUI_TEST
CANWorker::CANWorker(obd2* obd)
{
  qDebug() << "Creating CAN worker...";

  /* initialise diagnostics data */
  ObdMsg.channelB = 0;
  ObdMsg.requestB = "010D"; /* speed */
  ObdMsg.channelA = 0;
  ObdMsg.requestA = "010C"; /* rpm */
  ObdMsg.connectionFault = true;

  qRegisterMetaType<diagMsg_t>("diagMsg_t");

  m_obd = obd;
}
#else
CANWorker::CANWorker()
{
  qDebug() << "Creating CAN worker...";

  /* initialise diagnostics data */
  ObdMsg.channelB = 0;
  ObdMsg.requestB = "010D"; /* speed */
  ObdMsg.channelA = 0;
  ObdMsg.requestA = "010C"; /* rpm */
  ObdMsg.connectionFault = true;

  qRegisterMetaType<diagMsg_t>("diagMsg_t");


}
#endif

/**
 * @brief Destroy the CANWorker::CANWorker object
 * 
 */
CANWorker::~CANWorker()
{
  delete this;
}

/**
 * @brief 
 * 
 */
void CANWorker::GetDiagData()
{

  /* setup fast data publishing callback */
  diagTimer = new QTimer(this);
  connect(diagTimer, SIGNAL(timeout()), this, SLOT(PublishDiagData()));
  diagTimer->start(1000); //msecs

  m_running = true;
  while (m_running)
  {
	//qDebug() << "get data";
	//sleep(1);
#ifndef GUI_TEST
    if (m_obd->connected)
    {
	//cout << m_obd->send_cmd(ObdMsg.requestA, true) << endl;
      ObdMsg.connectionFault = false;
      ObdMsg.channelA = m_obd->decoded_cmd(ObdMsg.requestA);
      
    }
    else 
    { 
        ObdMsg.connectionFault = true; 
	    //DummyData();
    	usleep(50000); // JB: this time should not exceed the publishing timer interval 
    }
    /* publish the fast channel data as fast as possible */
    emit CANPublishDiagTx(&ObdMsg);
#endif

    /* currently blocking the executive so process any pending events now */
    qApp->processEvents();
  }
}

/**
 * @brief Receives a request from the diagnostics view to start logging user selected parameters
 * 
 * @param logParams 
 */
void CANWorker::LogRequestRx(QVector<QString> logParams)
{
  qDebug() << "CANWorker: logging requested";
  /* stop live data acquisition */
  //m_running = false;  //fast channel
  //diagTimer->stop();  //slow channel



}

/**
 * @brief 
 * 
 */
void CANWorker::GetLogData()
{

}

/* if the timer elapses before data is ready, 
	this signal is blocked until qApp->processEvents() is called 
	in the GetDiagData() loop */
/**
 * @brief Callback method invoked when diagnostics timer elapses. Publishes slow channel data (air temp, fuel etc)
 * 
 */
void CANWorker::PublishDiagData()
{
  qDebug() << "Publishing diag...";

#ifdef GUI_TEST
  DummyData();
#else
  ObdMsg.channelB = m_obd->decoded_cmd(ObdMsg.requestB);
#endif
  /* send data to GUI diagnostics viewer */
  emit CANPublishDiagTx(&ObdMsg);
}

/**
 * @brief Callback method invoked when logging timer elapses. Publishes diagnostics data to logger.
 * 
 */
void CANWorker::PublishLogData()
{
  /* TODO: implement logging signal */
  emit CANPublishLogTx();
}

/**
 * @brief changes the current requested data from the OBD2 bus based on requests from the user
 * 
 * @param dataRequested 
 * @param channel 
 */
void CANWorker::OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel)
{
  switch(dataRequested)
  {
    case SPEED: 
        {
            cout<<"OBD2: SPEED REQUESTED"<<endl;
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010D"; }
            else { ObdMsg.requestB = "010D"; }
            break;    
        }
        case RPM:
        {
            cout<<"OBD2: RPM REQUESTED"<<endl;
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010C"; }
            else { ObdMsg.requestB = "010C"; }
            break;    
        }
        case AIR_TEMP:
        {
            cout<<"OBD2: AIR TEMP REQUESTED"<<endl;
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010F"; }
            else { ObdMsg.requestB = "010F"; }
            break;    
        }
        case THROTTLE:
        {
	          qDebug() << "OBD2: THROTTLE POSITION REQUESTED";
            if(channel == CHANNEL_A) { ObdMsg.requestA = "0111"; }
            else { ObdMsg.requestB = "0111"; }
            break;           
        }
        case GEAR:
        {
	          qDebug() << "OBD2: CURRENT GEAR REQUESTED";
            if(channel == CHANNEL_A) { ObdMsg.requestA = "01A4"; }
            else { ObdMsg.requestB = "01A4"; }
            break;           
        }
        case FUEL_PRESSURE:
        {
	          qDebug() << "OBD2: FUEL PRESSURE REQUESTED";
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010A"; }
            else { ObdMsg.requestB = "010A"; }
            break;           
        }
        case ENGINE_LOAD:
        {
	          qDebug() << "OBD2: ENGINE LOAD REQUESTED";
            if(channel == CHANNEL_A) { ObdMsg.requestA = "0104"; }
            else { ObdMsg.requestB = "0104"; }
            break;           
        }
        case ENGINE_RUNTIME:
        {
	          qDebug() << "OBD2: ENGINE RUNTIME REQUESTED";
            if(channel == CHANNEL_A) { ObdMsg.requestA = "011F"; }
            else { ObdMsg.requestB = "011F"; }
            break;           
        }
        default: qDebug() << " OBD2: DATA REQUEST ERROR";
  }
}

/**
 * @brief 
 * 
 */
void CANWorker::DummyData()
{
  // dummy data 
    if (ObdMsg.channelA < 50 )
    {
        ObdMsg.channelA++;
    }
    else
    {
        ObdMsg.channelA = 0;
    }
    
    if (ObdMsg.channelB < 30)
    {
        ObdMsg.channelB = ObdMsg.channelB + 6;
    }
    else
    {
        ObdMsg.channelB = 0;
    }
    
    ObdMsg.connectionFault = false;  
}
				  


