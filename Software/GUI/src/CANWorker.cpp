#include "CANWorker.h"
#include <QtCore>
#include <iostream>
#include <unistd.h>
#include <QThread>

using namespace std;

CANWorker::CANWorker()
{
  qDebug() << "Creating CAN worker...";

  /* initialise diagnostics data */
  ObdMsg.channelB = 0;
  ObdMsg.requestB = "010D"; /* speed */
  ObdMsg.channelA = 0;
  ObdMsg.requestA = "010C"; /* rpm */
  ObdMsg.connectionFault = true;

}

CANWorker::~CANWorker()
{
  delete this;
}

void CANWorker::GetDiagData()
{
  m_obd = new obd2("/dev/rfcomm0");

  /* setup fast data publishing callback */
  diagTimer = new QTimer(this);
  connect(diagTimer, SIGNAL(timeout()), this, SLOT(PublishDiagData()));
  diagTimer->start(DIAG_RATE); //msecs

  m_running = true;
  while (m_running)
  {
	//qDebug() << "get data";
	//sleep(1);

    if (m_obd->connected)
    {
	//cout << m_obd->send_cmd(ObdMsg.requestA, true) << endl;
      ObdMsg.connectionFault = false;
      ObdMsg.channelA = m_obd->decoded_cmd(ObdMsg.requestA);
      ObdMsg.channelB = m_obd->decoded_cmd(ObdMsg.requestB);
    }
    else 
    { 
	ObdMsg.connectionFault = true; 
	//DummyData();
    	usleep(50000); /* JB: this time should not exceed the publishing timer interval */
    }
	/* currently blocking the executive so process any pending events now */
        qApp->processEvents();
  }
}

void CANWorker::GetLogData()
{

}

/* if the timer elapses before data is ready, 
	this signal is blocked until qApp->processEvents() is called 
	in the GetDiagData() loop */
void CANWorker::PublishDiagData()
{
  qDebug() << "Publishing diag...";

  /* send data to GUI diagnostics viewer */
  emit CANPublishDiagTx(&ObdMsg);
}

void CANWorker::PublishLogData()
{
  /* TODO: implement logging signal */
  emit CANPublishLogTx();
}

/* @brief: this slot changes the current requested data from the OBD2 bus based on requests from the user */
void CANWorker::OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel)
{
  switch(dataRequested)
  {
    case SPEED: 
        {
            cout<<"OBD2: SPEED REQUESTED"<<endl;
            if(channel == CHANNEL_A)
            {
                ObdMsg.requestA = "010D";
            }
            else
            {
                ObdMsg.requestB = "010D";
            } 
            break;    
        }
        case RPM:
        {
            cout<<"OBD2: RPM REQUESTED"<<endl;
           if(channel == CHANNEL_A)
            {
                ObdMsg.requestA = "010C";
            }
            else
            {
                ObdMsg.requestB = "010C";
            } 
            break;    
        }
        case AIR_TEMP:
        {
            cout<<"OBD2: AIR TEMP REQUESTED"<<endl;
            if(channel == CHANNEL_A)
            {
                ObdMsg.requestA = "010F";
            }
            else
            {
                ObdMsg.requestB = "010F";
            } 
            break;    
        }
        case THROTTLE:
        {
	  qDebug() << "OBD2: THROTTLE POSITION REQUESTED";
            if(channel == CHANNEL_A)
            {
                ObdMsg.requestA = "0111";
            }
            else
            {
                ObdMsg.requestB = "0111";
            }
            break;           
        }
  default: qDebug() << " OBD2: DATA REQUEST ERROR";
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
				  


