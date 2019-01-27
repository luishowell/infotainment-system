#include "CANThread.h"
#include <QtCore>
//#include <stdio.h>
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

    /* setup periodic data publishing callback */
    QTimer timer;
    connect(&timer, SIGNAL(timeout()), this, SLOT(PublishDiagData()), Qt::DirectConnection);
    //timer.start(DIAG_RATE); //msecs
    timer.start(1000); //msecs


    /* init diagnostics data */
    m_msg.speed = 0;
    m_msg.rpm = 0;
    m_msg.fuel = FUEL_CAPACITY; //litres
    m_msg.connectionFault = true;

    /* OBD2 converter class */
    
    m_obd = new obd2("/dev/rfcomm0");

    

    /* kick off the thread */
    exec();
}

/* @brief: Periodic callback method that publishes decoded CAN bus 
                        messages to the diagnostics viewer in the GUI thread */
void CANThread::PublishDiagData()
{
    cout<<"Publishing diag..."<<endl;

    
    //m_msg.connectionFault = !m_obd2->connected;
   
    if (m_obd->connected){
        //cout<<"RPM Request: "<<m_obd->send_cmd(command)<<endl;

        m_msg.connectionFault = false;    
        m_msg.speed = m_obd->decoded_cmd("010D");
        m_msg.rpm = m_obd->decoded_cmd("010C");
        m_msg.intakeAirTemp = m_obd->decoded_cmd("010F");
        m_msg.fuel = 50;
    
    }
    else{
        cout<<"Not Conected"<<endl;
    }
    

    /* dummy data */
    /*
    if (m_msg.speed < 50 )
    {
        m_msg.speed++;
    }
    else
    {
        m_msg.speed = 0;
    }
    
    if (m_msg.rpm < 30)
    {
        m_msg.rpm = m_msg.rpm + 3;
    }
    else
    {
        m_msg.rpm = 0;
    }
    
    if (m_msg.fuel > 0)
    {
        m_msg.fuel--; 
    }
    else
    {
        m_msg.fuel = 65;
    }
    m_msg.connectionFault = false;  
*/
    
    
    /* send data to the GUI's diagnostics viewer */
    emit CANPublishDiagTx(&m_msg);
}