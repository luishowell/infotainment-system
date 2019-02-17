#include "config.h"
#include "CANThread.h"
#include <QtCore>
#include "Timer.h"
#include <iostream>
#include <string>

using namespace std;

CANThread::CANThread()
{

}

CANThread::~CANThread()
{
    
    delete this;
}

void CANThread::run()
{
    qDebug() << "Starting CAN thread...";

    /* setup fast data publishing callback */
    //QTimer timer(this);
    //connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    //timer.start(DIAG_RATE); //msecs

    /* setup logging data publishing callback */
    // QTimer logTimer;
    //connect(&logTimer, SIGNAL(timeout()), this, SLOT(PublishLogData()), Qt::DirectConnection);
    //logTimer.start(LOGGING_RATE); //msecs
   
    /* kick off the thread */
    exec();
}

/* JB: moved to worker class for now */
void CANThread::PublishDiagData()
{
  qDebug() << "Publishing diag...";
  
}

/*
void CANThread::DummyData()
{
  // dummy data 
    if (m_msg.channelA < 50 )
    {
        m_msg.channelA++;
    }
    else
    {
        m_msg.channelA = 0;
    }
    
    if (m_msg.channelB < 30)
    {
        m_msg.channelB = m_msg.channelB + 6;
    }
    else
    {
        m_msg.channelB = 0;
    }
    
    m_msg.connectionFault = false;  
}
*/


