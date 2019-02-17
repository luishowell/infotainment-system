/**
 * @file Diagnostics.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QDial>
#include <Qt>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlProperty>

//#include <stdio.h>
#include <iostream>
#include "Diagnostics.h" 
#include "config.h"

using namespace std;

/**
 * @brief Construct a new Diagnostics:: Diagnostics object
 * 
 * @param parent 
 */
Diagnostics::Diagnostics(QWidget *parent) : QWidget(parent) 
 {   
   setFixedSize(widgetSize);
   CreateComponents();
   CreateLayout();    
   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 
   connect(this, SIGNAL (NewChannelRequest(diagParams_t, obd2Channel_t)), parent, SLOT (OnNewChannelRequest(diagParams_t, obd2Channel_t))); 

   ConnectButtons();
   

   /* CAN bus initially assumed disconnected until the CAN thread specifies no connection fault */
   canConnectionFlag = false;
 }

/**
 * @brief 
 * 
 */
void Diagnostics::CreateComponents()
{
   /* set up speedometer */
   QQuickView *speedoQML = new QQuickView();
   m_speedometer = QWidget::createWindowContainer(speedoQML, this);  
   m_speedometer->setFixedSize(175, 175);
#ifdef GUI_TEST
   speedoQML->setSource(QUrl::fromLocalFile("/home/pi/Desktop/infotainment-system/Software/GUI/src/Speedometer.qml"));
#else
   speedoQML->setSource(QUrl::fromLocalFile("../GUI/src/Speedometer.qml"));
#endif
   speedoQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_speedObject = speedoQML->rootObject();

   /* set up RPM gauge */
   QQuickView *rpmQML = new QQuickView();
   m_rpmGauge = QWidget::createWindowContainer(rpmQML, this);  
   m_rpmGauge->setFixedSize(175, 175);
#ifdef GUI_TEST
   rpmQML->setSource(QUrl::fromLocalFile("./GUI/src/RpmGauge.qml"));
#else
   rpmQML->setSource(QUrl::fromLocalFile("../GUI/src/RpmGauge.qml"));
#endif
   rpmQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_rpmObject = rpmQML->rootObject();

   /* set up intake air temperature gauge */
   QQuickView *airTempQML = new QQuickView();
   m_airTempGauge = QWidget::createWindowContainer(airTempQML, this);  
   m_airTempGauge->setFixedSize(100, 175);
#ifdef GUI_TEST
   airTempQML->setSource(QUrl::fromLocalFile("./GUI/src/AirTempGauge.qml"));
#else
   airTempQML->setSource(QUrl::fromLocalFile("../GUI/src/AirTempGauge.qml"));
#endif
   airTempQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_airTempObject = airTempQML->rootObject();

   /* set up throttle gauge */
   QQuickView *throttleQML = new QQuickView();
   m_throttleGauge = QWidget::createWindowContainer(throttleQML, this);  
   m_throttleGauge->setFixedSize(100, 175);
#ifdef GUI_TEST
   throttleQML->setSource(QUrl::fromLocalFile("./GUI/src/ThrottleGauge.qml"));
#else
   throttleQML->setSource(QUrl::fromLocalFile("../GUI/src/ThrottleGauge.qml"));
#endif
   throttleQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_throttleObject = throttleQML->rootObject();

   /* set up selection buttons */
   m_rpmButton = new QPushButton("RPM");
   m_speedButton = new QPushButton("Speed");
   m_intakeAirTempButton = new QPushButton("Intake Air \nTemperature");
   m_throttleButton = new QPushButton("Throttle \nPosition");

   const QSize btnSize = QSize(120, 100);
   m_rpmButton->setFixedSize(btnSize);
   m_speedButton->setFixedSize(btnSize);
   m_intakeAirTempButton->setFixedSize(btnSize);
   m_throttleButton->setFixedSize(btnSize);

   m_logButton = new QPushButton("Log Journey");
   m_logButton->setFixedSize(400, 50);
}

/**
 * @brief 
 * 
 */
void Diagnostics::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);

   QGroupBox* titleBox = new QGroupBox("Diagnostics", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);

   boxLayout->setVerticalSpacing(10);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   
   /* create individual layouts for gauges */
   speedBox = new QGroupBox("Speed", titleBox);
   speedBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *speedLayout = new QVBoxLayout(speedBox);
   speedLayout->addWidget(m_speedometer);

   rpmBox = new QGroupBox("RPM", titleBox);
   rpmBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *rpmLayout = new QVBoxLayout(rpmBox);
   rpmLayout->addWidget(m_rpmGauge);

   airTempBox = new QGroupBox("Intake Air Temperature", titleBox);
   airTempBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *airTempLayout = new QHBoxLayout(airTempBox);
   airTempLayout->addWidget(m_airTempGauge);

   throttleBox = new QGroupBox("Throttle Position", titleBox);
   throttleBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *throttleLayout = new QHBoxLayout(throttleBox);
   throttleLayout->addWidget(m_throttleGauge);
   
   /* parameter selection box */
   selectBox = new QGroupBox("Parameters", titleBox);
   selectBox->setAlignment(Qt::AlignHCenter);
   selectBox->setFixedSize(250, 250);
   QHBoxLayout *selectLayout = new QHBoxLayout(selectBox);
   QVBoxLayout *selectLeft = new QVBoxLayout(selectBox);
   QVBoxLayout *selectRight = new QVBoxLayout(selectBox);
   selectLeft->addWidget(m_rpmButton);
   selectRight->addWidget(m_speedButton);
   selectLeft->addWidget(m_intakeAirTempButton);
   selectRight->addWidget(m_throttleButton);
   selectLeft->setAlignment(Qt::AlignLeft);
   selectRight->setAlignment(Qt::AlignHCenter);
   selectLayout->addLayout(selectLeft);
   selectLayout->addLayout(selectRight);

   airTempBox->setFixedSize(200,225);
   throttleBox->setFixedSize(200,225);
   speedBox->setFixedSize(200,225);
   rpmBox->setFixedSize(200,225);
   titleBox->setFixedSize(WIDGET_SIZE_X-30, WIDGET_SIZE_Y-100);

   /* default shown gauges */
   boxLayout->addWidget(selectBox, 1, 3);
   boxLayout->addWidget(speedBox, 1, 2);
   boxLayout->addWidget(rpmBox, 1, 1);
   boxLayout->addWidget(throttleBox, 1, 2);
   boxLayout->addWidget(m_logButton, 2, 1);

/*
   currentRightGauge = speedBox;
   m_currentRightObj = m_speedObject;
   currentLeftGauge = rpmBox;
   m_currentLeftObj = m_rpmObject;
*/

   currentRightChannel.box = speedBox;
   currentRightChannel.obj = m_speedObject;
   currentLeftChannel.box = rpmBox;
   currentLeftChannel.obj = m_rpmObject;

   /* default hidden gauges */
   boxLayout->addWidget(airTempBox, 1, 1);
   airTempBox->hide();
   throttleBox->hide();

   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);

   setLayout(vLayout);

}

/**
 * @brief 
 * 
 * @param msg 
 */
void Diagnostics::DiagDataRx(diagMsg_t* msg)
{
   if (msg->connectionFault == true)
   {
      cout<<"WARNING: no connection to CAN bus"<<endl;

      if(canConnectionFlag == true)
      {
         m_speedObject->setProperty("value", 0);
         m_rpmObject->setProperty("value", 0);
         canConnectionFlag = false; 
      }    
   }
   else 
   {
      if(canConnectionFlag == false)
      {
         cout<<"CAN bus connection established"<<endl;
         canConnectionFlag = true;
      }
       
      //cout<<"/******DIAG******/"<<endl;
      //cout<<"Speed:"<< msg->speed << endl;
      //cout<<"RPM:"<< msg->rpm<<endl;
      //cout<<"/****************/"<<endl;
   int leftVal = 0;
      if (currentLeftChannel.obj == m_rpmObject)
	{
		leftVal = (msg->channelA) / 100;
	}
	else
	{
		leftVal = msg->channelA;
	}
      currentLeftChannel.obj->setProperty("value", leftVal);
      currentRightChannel.obj->setProperty("value", msg->channelB);
   }
   
}

/**
 * @brief 
 * 
 */
void Diagnostics::ConnectButtons()
{
   //connect(this, SIGNAL (DiagDataChange(diagData_t)), this, SLOT (ChangeDiagDisplay(diagData_t)));
   connect(m_rpmButton, SIGNAL (clicked()), this, SLOT (ShowRpmGauge()));
   connect(m_speedButton, SIGNAL (clicked()), this, SLOT (ShowSpeedGauge()));
   connect(m_intakeAirTempButton, SIGNAL (clicked()), this, SLOT (ShowAirTempGauge()));
   connect(m_throttleButton, SIGNAL (clicked()), this, SLOT (ShowThrottleGauge()));
   connect(m_logButton, SIGNAL (clicked()), this, SLOT (JourneyLogRequest()));

}

/* public slots */
/**
 * @brief 
 * 
 */
void Diagnostics::ShowAirTempGauge()
{
   if (currentLeftGauge != airTempBox)
   {
      currentLeftChannel.box->hide();
      airTempBox->show();
      currentLeftChannel.box = airTempBox;

      /* request intake air temperate to be obtained from the OBD2 thread */
      emit NewChannelRequest(AIR_TEMP, CHANNEL_A);
   }
}

/**
 * @brief 
 * 
 */
void Diagnostics::ShowSpeedGauge()
{
   if (currentRightGauge != speedBox)
   {
      currentRightChannel.box->hide();
      speedBox->show();
      currentRightChannel.box = speedBox;

      /* request speed data to be obtained from the OBD2 thread */
      emit NewChannelRequest(SPEED, CHANNEL_B);
   }
}

/**
 * @brief 
 * 
 */
void Diagnostics::ShowRpmGauge()
{
   if (currentLeftGauge != rpmBox)
   {
      currentLeftChannel.box->hide();
      rpmBox->show();
      currentLeftChannel.box = rpmBox;

      /* request RPM data to be obtained from the OBD2 thread */
      emit NewChannelRequest(RPM, CHANNEL_A);
   }     
}

/**
 * @brief 
 * 
 */
void Diagnostics::ShowThrottleGauge()
{
   if (currentRightGauge != throttleBox)
   {
      currentRightChannel.box->hide();
      throttleBox->show();
      currentRightChannel.box = throttleBox;

      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(THROTTLE, CHANNEL_B);
   }  
}

/**
 * @brief 
 * 
 */
void Diagnostics::JourneyLogRequest()
{
   cout<<"LOG REQUESTED"<<endl;

   /* TODO: implement log request signal*/
   /* send log request to state machine */
   emit StartLogging();
}

/**
 * @brief 
 * 
 */
void Diagnostics::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}