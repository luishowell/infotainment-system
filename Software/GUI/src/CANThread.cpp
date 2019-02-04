#include "CANThread.h"
#include <QtCore>
#include "Timer.h"
#include <iostream>
#include "config.h"
#include <string>

using namespace std;

CANThread::CANThread()
{
    
}

void CANThread::run()
{
    cout<<"Starting CAN thread..."<<endl;

    /* setup fast data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    timer.start(DIAG_RATE); //msecs

    /* setup logging data publishing callback */
    QTimer logTimer;
    connect(&logTimer, SIGNAL(timeout()), this, SLOT(PublishLogData()), Qt::DirectConnection);
    logTimer.start(LOGGING_RATE); //msecs

    /* init diagnostics data */
    m_msg.channelB = 0;
    m_msg.requestB = "010D"; //speed
    m_msg.channelA = 0;
    m_msg.requestA = "010C"; //rpm
    m_msg.connectionFault = true;

#ifndef GUI_TEST
    /* OBD2 converter class */
    m_obd = new obd2("/dev/rfcomm0");
#endif

    /* kick off the thread */
    exec();
}

/* @brief: Periodic callback method that publishes decoded CAN bus 
                        messages to the diagnostics viewer in the GUI thread */
void CANThread::PublishDiagData()
{
    //cout<<"Publishing diag..."<<endl;
#ifdef GUI_TEST
    DummyData();
#else
    if (m_obd->connected)
    {
        m_msg.connectionFault = false;    
        m_msg.channelA = m_obd->decoded_cmd(m_msg.requestA);
        m_msg.channelB = m_obd->decoded_cmd(m_msg.requestB);
    }
    else
    {
        m_msg.connectionFault = true;
        cout<<"Not Connected"<<endl;
    }
 #endif   
    
    /* send data to the GUI's diagnostics viewer */
    emit CANPublishDiagTx(&m_msg);
}

void CANThread::PublishLogData()
{
    //cout<<"publish logging"<<endl;

    /* TODO: implement logging signal */
    emit CANPublishLogTx();
}

void CANThread::DummyData()
{
    /* dummy data */
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

/* @brief: this slot changes the current requested data from the OBD2 bus based on requests from the user */
void CANThread::OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel)
{
    switch(dataRequested)
    {
        case SPEED: 
        {
            cout<<"OBD2: SPEED REQUESTED"<<endl;
            if(channel == CHANNEL_A)
            {
                m_msg.requestA = "010D";
            }
            else
            {
                m_msg.requestB = "010D";
            } 
            break;    
        }
        case RPM:
        {
            cout<<"OBD2: RPM REQUESTED"<<endl;
           if(channel == CHANNEL_A)
            {
                m_msg.requestA = "010C";
            }
            else
            {
                m_msg.requestB = "010C";
            } 
            break;    
        }
        case AIR_TEMP:
        {
            cout<<"OBD2: AIR TEMP REQUESTED"<<endl;
            if(channel == CHANNEL_A)
            {
                m_msg.requestA = "010F";
            }
            else
            {
                m_msg.requestB = "010F";
            } 
            break;    
        }
        case THROTTLE:
        {
            cout<<"OBD2: THROTTLE POSITION REQUESTED"<<endl;
            if(channel == CHANNEL_A)
            {
                m_msg.requestA = "0111";
            }
            else
            {
                m_msg.requestB = "0111";
            }
            break;           
        }
        default: cout<<" OBD2: DATA REQUEST ERROR"<<endl;
    }
}