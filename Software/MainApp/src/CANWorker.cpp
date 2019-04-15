/**
 * @file CANWorker.cpp
 * @author Jamie Brown
 * @brief Implementation of CANWorker.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "CANWorker.h"
#include "Hash.h"
#include "Mutex.h"

#include <QtCore>

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <QThread>
#include <chrono>
#include <ctime> 

//extern QMutex Mutex::OBD2Mutex;

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

}

CANWorker::~CANWorker()
{
  delete this;
}

void CANWorker::GetDiagData()
{
  bool locked;

  diagTimer->start(1000); //msecs
  
  m_running = true;
  while (m_running)
  {

#ifndef RPI
	qDebug() << "CAN WORKER: Get fast data";
	sleep(1);
#endif
    if (m_obd->connected)
    {
      
      ObdMsg.connectionFault = false;
      if ( Mutex::TryOBD2() )
      {
        ObdMsg.channelA = m_obd->decoded_cmd(ObdMsg.requestA, true);
        Mutex::UnlockOBD2();
      }
      else
      {
        qDebug() << "CAN WORKER: OBD2 bus is currently busy";
      }
    }
    else 
    { 
      //qDebug() << "CAN WORKER: connection fault";
      ObdMsg.connectionFault = true; 
    	usleep(1000); // JB: this time should not exceed the publishing timer interval 

    }
    /* publish the fast channel data as fast as possible */
    emit CANPublishDiagTx(&ObdMsg);

    /* currently blocking the executive so process any pending events now */
    qApp->processEvents();
  }
}

void CANWorker::LogRequestRx(QVector<QString> logParams, bool start)
{
  qDebug() << "CAN WORKER: logging requested" << start;
  std::string paramName;

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
      /* get current time */
      auto endTime = std::chrono::system_clock::now();
      std::chrono::duration<double> currentTime = endTime - startTime;
      m_logFile << currentTime.count() << ",";

      for (int idx = 0; idx < paramSize; idx++)
      {
        /* write to csv file */
        m_logFile << m_obd->decoded_cmd(logParams[idx].toStdString(), true);
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
void CANWorker::PublishDiagData()
{

  if (Mutex::TryOBD2())
  {
    ObdMsg.channelB = m_obd->decoded_cmd(ObdMsg.requestB, true);
    Mutex::UnlockOBD2();
  }
  else
  {
    qDebug() << "CAN WORKER: obd2 busy (diag timer)";
  }
  
  /* send data to GUI diagnostics viewer */
  emit CANPublishDiagTx(&ObdMsg);
}

void CANWorker::PublishLogData()
{
  /* TODO: implement logging signal */
  emit CANPublishLogTx();
}

void CANWorker::OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel)
{
  switch(dataRequested)
  {
    case SPEED: 
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010D"; }
            else { ObdMsg.requestB = "010D"; }
            break;    
        }
        case RPM:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010C"; }
            else { ObdMsg.requestB = "010C"; }
            break;    
        }
        case AIR_TEMP:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010F"; }
            else { ObdMsg.requestB = "010F"; }
            break;    
        }
        case THROTTLE:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "0111"; }
            else { ObdMsg.requestB = "0111"; }
            break;           
        }
        case GEAR:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "01A4"; }
            else { ObdMsg.requestB = "01A4"; }
            break;           
        }
        case FUEL_PRESSURE:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "010A"; }
            else { ObdMsg.requestB = "010A"; }
            break;           
        }
        case ENGINE_LOAD:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "0104"; }
            else { ObdMsg.requestB = "0104"; }
            break;           
        }
        case ENGINE_RUNTIME:
        {
            if(channel == CHANNEL_A) { ObdMsg.requestA = "011F"; }
            else { ObdMsg.requestB = "011F"; }
            break;           
        }
        default: qDebug() << " OBD2: data request error";
  }
}

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
				  


