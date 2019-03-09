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
#include "Hash.h"

#include <QtCore>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <QThread>
#include <chrono>
#include <ctime> 

using namespace std;

CANWorker::CANWorker(obd2* obd)
{
  qDebug() << "CAN WORKER: creating...";

  /* initialise diagnostics data */
  ObdMsg.channelB = 0;
  ObdMsg.requestB = "010D"; /* speed */
  ObdMsg.channelA = 0;
  ObdMsg.requestA = "010C"; /* rpm */
  ObdMsg.connectionFault = true;

  qRegisterMetaType<diagMsg_t>("diagMsg_t");

  m_obd = obd;

  /* setup fast data publishing callback */
  diagTimer = new QTimer(this);
  connect(diagTimer, SIGNAL(timeout()), this, SLOT(PublishDiagData()));

  /* create data logging file*/
  //m_logFile = new ofstream;git
}

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
  diagTimer->start(1000); //msecs
  
  m_running = true;
  while (m_running)
  {
	qDebug() << "CAN WORKER: Get fast data";
	sleep(1);
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
    	usleep(1000); // JB: this time should not exceed the publishing timer interval 
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
void CANWorker::LogRequestRx(QVector<QString> logParams, bool start)
{
  qDebug() << "CAN WORKER: logging requested" << start;

  if (start)
  {
    /* start timing */
    auto startTime = std::chrono::system_clock::now();

    /* open data logging file */
    m_logFile.open("DataLog.csv");
    if(!m_logFile.is_open())
    {
      qDebug() << "CAN WORKER: error opening log file";
    }

    int paramSize = logParams.size();
    QVector<float> logMsg;
    for (int idx = 0; idx < paramSize; idx++)
    {
      qDebug() << logParams[idx];
    }

    /* stop live data acquisition */
    diagTimer->stop();  //slow channel
    
    /* column titles for csv file */
    m_logFile << "Time,";
    for (int idx = 0; idx < paramSize; idx++)
    {
      m_logFile << Hash::PID2Name(logParams[idx]);
      if (idx == paramSize - 1)
      {
        m_logFile << endl << endl;
      }
      else
      {
        m_logFile << ",";
      }
    }

    while(m_running) //placeholder
    {
      qDebug() << "CAN WORKER: logging";
      sleep(1);

      /* get current time */
      auto endTime = std::chrono::system_clock::now();
      std::chrono::duration<double> currentTime = endTime - startTime;
      m_logFile << currentTime.count() << ",";

      for (int idx = 0; idx < paramSize; idx++)
      {
        /* write to csv file */
        m_logFile << m_obd->decoded_cmd(logParams[idx].toStdString());
        if (idx == paramSize - 1)
        {
          m_logFile << endl;
        }
        else
        {
          m_logFile << ",";
        }
      }
      qApp->processEvents();
    }
  }
  else
  {
    m_running = 0;
    qDebug() << "CAN WORKER: logging stopped";
    m_logFile.close();

    /* Start default live data acquisition routine */
    GetDiagData();

  }
  
  
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
	qDebug() << "CAN WORKER: get slow data";

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
				  


