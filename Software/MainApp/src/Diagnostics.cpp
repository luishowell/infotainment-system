/**
 * @file Diagnostics.cpp
 * @author Jamie Brown
 * @brief Implementation of Diagnostics.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "Diagnostics.h" 
#include "config.h"
#include "Hash.h"
#include "MMA8652FCR1.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedLayout>
#include <QGroupBox>
#include <QDial>
#include <Qt>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlProperty>
#include <QPixmap>

#include <vector>
#include <string>
#include <iostream>

using namespace std;

Diagnostics::Diagnostics(QWidget *parent, obd2* myObd, MMA8652FCR1* acc) : QWidget(parent) 
 {   
   m_acc = acc;
    
   std::vector<std::string> testVec;
   testVec.push_back("0C");
   testVec.push_back("0D");
   testVec.push_back("1F");
   testVec.push_back("04");
   testVec.push_back("A4");
   testVec.push_back("0A");

   obd = myObd;
   //m_logWindow = new LoggerWindow(testVec);
   m_logWindow = new LoggerWindow(obd->supported_pids, this);
   m_logWindow->setFixedSize(400, 300);
 
   setFixedSize(widgetSize);
   CreateComponents();
   CreateLayout();    
   connect(this, SIGNAL (NewChannelRequest(diagParams_t, obd2Channel_t)), parent, SLOT (OnNewChannelRequest(diagParams_t, obd2Channel_t))); 
   ConnectButtons();

   /* CAN bus initially assumed disconnected until the CAN thread specifies no connection fault */
   canConnectionFlag = false;

   qRegisterMetaType<diagParams_t>("diagParams_t");
   qRegisterMetaType<obd2Channel_t>("obd2Channel_t");

 }

void Diagnostics::CreateComponents()
{
   qDebug() << "DIAGNOSTICS: creating components";
   const QSize gaugeSize = QSize(100, 175);
   const QSize dialSize = QSize(140, 140);

   /* create g-force meter */
   m_accGauge = new AccGauge(1, m_acc->staticVals);

   /* set up speedometer */
   QQuickView *speedoQML = new QQuickView();
   m_speedometer = QWidget::createWindowContainer(speedoQML, this);  
   m_speedometer->setFixedSize(dialSize);
   speedoQML->setSource(QUrl::fromLocalFile("./MainApp/src/Speedometer.qml"));
   speedoQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_speedObject = speedoQML->rootObject();

   /* set up RPM gauge */
   QQuickView *rpmQML = new QQuickView();
   m_rpmGauge = QWidget::createWindowContainer(rpmQML, this);  
   m_rpmGauge->setFixedSize(dialSize);
   rpmQML->setSource(QUrl::fromLocalFile("./MainApp/src/RpmGauge.qml"));
   rpmQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_rpmObject = rpmQML->rootObject();

   /* set up intake air temperature gauge */
   QQuickView *airTempQML = new QQuickView();
   m_airTempGauge = QWidget::createWindowContainer(airTempQML, this);  
   m_airTempGauge->setFixedSize(gaugeSize);
   airTempQML->setSource(QUrl::fromLocalFile("./MainApp/src/AirTempGauge.qml"));
   airTempQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_airTempObject = airTempQML->rootObject();

   /* set up throttle gauge */
   QQuickView *throttleQML = new QQuickView();
   m_throttleGauge = QWidget::createWindowContainer(throttleQML, this);  
   m_throttleGauge->setFixedSize(gaugeSize);
   throttleQML->setSource(QUrl::fromLocalFile("./MainApp/src/ThrottleGauge.qml"));
   throttleQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_throttleObject = throttleQML->rootObject();

   /* set up gear gauge */
   QQuickView *gearQML = new QQuickView();
   m_gearGauge = QWidget::createWindowContainer(gearQML, this);  
   m_gearGauge->setFixedSize(gaugeSize);
   gearQML->setSource(QUrl::fromLocalFile("./MainApp/src/ThrottleGauge.qml"));
   gearQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_gearObject = gearQML->rootObject();

   /* set up fuel pressure gauge */
   QQuickView *fuelPressureQML = new QQuickView();
   m_fuelPressureGauge = QWidget::createWindowContainer(fuelPressureQML, this);  
   m_fuelPressureGauge->setFixedSize(gaugeSize);
   fuelPressureQML->setSource(QUrl::fromLocalFile("./MainApp/src/FuelPressureGauge.qml"));
   fuelPressureQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_fuelPressureObject = fuelPressureQML->rootObject();

   /* set up engine runtime gauge */
   QQuickView *engineRuntimeQML = new QQuickView();
   m_engineRuntimeGauge = QWidget::createWindowContainer(engineRuntimeQML, this);  
   m_engineRuntimeGauge->setFixedSize(gaugeSize);
   engineRuntimeQML->setSource(QUrl::fromLocalFile("./MainApp/src/ThrottleGauge.qml"));
   engineRuntimeQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_engineRuntimeObject = engineRuntimeQML->rootObject();
  
   /* set up engine load gauge */
   QQuickView *engineLoadQML = new QQuickView();
   m_engineLoadGauge = QWidget::createWindowContainer(engineLoadQML, this);  
   m_engineLoadGauge->setFixedSize(gaugeSize);
   engineLoadQML->setSource(QUrl::fromLocalFile("./MainApp/src/EngineLoadGauge.qml"));
   engineLoadQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_engineLoadObject = engineLoadQML->rootObject();

   qDebug() << "Buttons";
   /* set up selection buttons */
   m_rpmButton             = new QPushButton("RPM");
   m_speedButton           = new QPushButton("Speed");
   m_intakeAirTempButton   = new QPushButton("Intake Air \nTemperature");
   m_throttleButton        = new QPushButton("Throttle \nPosition");
   m_engineRuntimeButton   = new QPushButton("Engine \nRuntime");
   m_engineLoadButton      = new QPushButton("Engine \nLoad");
   m_gearButton            = new QPushButton("Current \nGear");
   m_fuelPressureButton    = new QPushButton("Fuel \nPressure");
   m_accButton             = new QPushButton("G-Force");

   const QSize btnSize = QSize(100, 50);
   m_rpmButton->setFixedSize(btnSize);
   m_speedButton->setFixedSize(btnSize);
   m_intakeAirTempButton->setFixedSize(btnSize);
   m_throttleButton->setFixedSize(btnSize);
   m_throttleButton->setFixedSize(btnSize);
   m_engineRuntimeButton->setFixedSize(btnSize);
   m_engineLoadButton->setFixedSize(btnSize);
   m_gearButton->setFixedSize(btnSize);
   m_fuelPressureButton->setFixedSize(btnSize);
   m_accButton->setFixedSize(btnSize);
   
   m_logButton = new QPushButton("Journey Logger");
   m_logButton->setFixedSize(400, 50);
}

void Diagnostics::CreateLayout()
{
   qDebug() << "DIAGNOSTICS: creating layout";

   int pidNum;
   int pidCnt;

   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);

   QGroupBox* titleBox = new QGroupBox("Diagnostics", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);

   boxLayout->setVerticalSpacing(10);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 
   
   /* create individual layouts for gauges */
   accBox = new QGroupBox("G-Force", titleBox);
   accBox->setAlignment(Qt::AlignHCenter);
   QPointer<QVBoxLayout> accLayout = new QVBoxLayout(accBox);
   accLayout->addWidget(m_accGauge);
   //accLayout->setAlignment(Qt::AlignHCenter);

   speedBox = new QGroupBox("Speed(KPH)", titleBox);
   m_speedLCD = new QLCDNumber();
   speedBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *speedLayout = new QVBoxLayout(speedBox);
   speedLayout->addWidget(m_speedometer);
   speedLayout->addWidget(m_speedLCD);
   speedLayout->setAlignment(Qt::AlignHCenter);

   rpmBox = new QGroupBox("RPM(x100/min)", titleBox);
   m_rpmLCD = new QLCDNumber();
   rpmBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *rpmLayout = new QVBoxLayout(rpmBox);
   rpmLayout->addWidget(m_rpmGauge);
   rpmLayout->addWidget(m_rpmLCD);
   rpmLayout->setAlignment(Qt::AlignHCenter);   

   airTempBox = new QGroupBox("Intake Air Temperature", titleBox);
   m_airTempLCD = new QLCDNumber();
   airTempBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *airTempLayout = new QHBoxLayout(airTempBox);
   airTempLayout->addWidget(m_airTempGauge);
   airTempLayout->setAlignment(Qt::AlignHCenter);   

   throttleBox = new QGroupBox("Throttle Position", titleBox);
   m_throttleLCD = new QLCDNumber();
   throttleBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *throttleLayout = new QStackedLayout(throttleBox);
   //throttleLayout->addWidget(m_throttleGauge);
   m_throttleGauge->hide();
   throttleLayout->addWidget(m_throttleLCD);
   throttleLayout->setAlignment(Qt::AlignHCenter);      

   gearBox = new QGroupBox("Current Gear", titleBox);
   m_gearLCD = new QLCDNumber();
   gearBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *gearLayout = new QStackedLayout(gearBox);
   gearLayout->addWidget(m_gearLCD);
   gearLayout->addWidget(m_gearGauge);
   gearLayout->setAlignment(Qt::AlignHCenter);      
 
   fuelPressureBox = new QGroupBox("Fuel Pressure", titleBox);
   m_fuelPressureLCD = new QLCDNumber();
   fuelPressureBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *fuelPressureLayout = new QHBoxLayout(fuelPressureBox);
   fuelPressureLayout->addWidget(m_fuelPressureGauge);
   //fuelPressureLayout->addWidget(m_fuelPressureLCD);
   fuelPressureLayout->setAlignment(Qt::AlignHCenter);      
   
   engineRuntimeBox = new QGroupBox("Engine Runtime", titleBox);
   m_engineRuntimeLCD = new QLCDNumber(engineRuntimeBox);
   engineRuntimeBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *engineRuntimeLayout = new QStackedLayout(engineRuntimeBox);
   engineRuntimeLayout->addWidget(m_engineRuntimeLCD); 
   engineRuntimeLayout->addWidget(m_engineRuntimeGauge); //JB: without this loads of random white space?? 
   engineRuntimeLayout->setAlignment(Qt::AlignHCenter);         

   engineLoadBox = new QGroupBox("Engine Load", titleBox);
   m_engineLoadLCD = new QLCDNumber();
   engineLoadBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *engineLoadLayout = new QStackedLayout(engineLoadBox);
   //engineLoadLayout->addWidget(m_engineLoadGauge);  
   m_engineLoadGauge->hide();
   engineLoadLayout->addWidget(m_engineLoadLCD);
   engineRuntimeLayout->setAlignment(Qt::AlignHCenter);         

   /* parameter selection box */
   selectBox = new QGroupBox("Parameters", titleBox);
   selectBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *selectLayout = new QHBoxLayout(selectBox);
   QVBoxLayout *selectLeft = new QVBoxLayout(selectBox);
   QVBoxLayout *selectRight = new QVBoxLayout(selectBox);

   selectLeft->addWidget(m_engineLoadButton);
   selectLeft->addWidget(m_rpmButton);
   selectLeft->addWidget(m_speedButton);
   selectLeft->addWidget(m_throttleButton);
   selectLeft->addWidget(m_engineRuntimeButton);
   selectRight->addWidget(m_gearButton);
   selectRight->addWidget(m_fuelPressureButton);
   selectRight->addWidget(m_intakeAirTempButton);
   selectRight->addWidget(m_accButton);

   m_engineLoadButton->setEnabled(false);
   m_rpmButton->setEnabled(false);
   m_speedButton->setEnabled(false);
   m_throttleButton->setEnabled(false);
   m_engineRuntimeButton->setEnabled(false);
   m_gearButton->setEnabled(false);
   m_fuelPressureButton->setEnabled(false);
   m_intakeAirTempButton->setEnabled(false);
   m_accButton->setEnabled(true);

   /* only enable selection buttons for the supported obd2 pids */
   QString QPid;
   pidNum = obd->supported_pids.size();
   for (pidCnt = 0; pidCnt < pidNum; pidCnt++)
   {
      switch (Hash::HashPID(obd->supported_pids[pidCnt])) // JB: fixed bug here (13/03/19)
      {
         /* fast channel buttons */
         case ENGINE_LOAD :      m_engineLoadButton->setEnabled(true);
                                 break;
         case RPM :              m_rpmButton->setEnabled(true);
                                 break;
         case SPEED :            m_speedButton->setEnabled(true);
                                 break;
         case THROTTLE :         m_throttleButton->setEnabled(true);
                                 break;
         case ENGINE_RUNTIME :   m_engineRuntimeButton->setEnabled(true);
                                 break;
         /* slow channel buttons */
         case FUEL_PRESSURE :    m_fuelPressureButton->setEnabled(true);
                                 break;
         case AIR_TEMP :         m_intakeAirTempButton->setEnabled(true);
                                 break;
         case GEAR :             m_gearButton->setEnabled(true);
                                 break;
         default :               break;
      }
   }
   
   selectLeft->setAlignment(Qt::AlignLeft);
   selectRight->setAlignment(Qt::AlignHCenter);
   selectLayout->addLayout(selectLeft);
   selectLayout->addLayout(selectRight);

   const QSize boxSize = QSize(200, 225);
   airTempBox->setFixedSize(boxSize);
   throttleBox->setFixedSize(boxSize);
   speedBox->setFixedSize(boxSize);
   rpmBox->setFixedSize(boxSize);
   gearBox->setFixedSize(boxSize);
   fuelPressureBox->setFixedSize(boxSize);
   engineLoadBox->setFixedSize(boxSize);
   engineRuntimeBox->setFixedSize(boxSize);
   accBox->setFixedSize(boxSize);
   
   titleBox->setFixedSize(WIDGET_SIZE_X-30, WIDGET_SIZE_Y-100);

   /* default shown gauges */
   boxLayout->addWidget(selectBox, 1, 4, 3, 3, Qt::AlignTop);
   boxLayout->addWidget(speedBox, 1, 1);
   boxLayout->addWidget(rpmBox, 1, 1);
   boxLayout->addWidget(throttleBox, 1, 1);
   boxLayout->addWidget(airTempBox, 1, 2, Qt::AlignLeft);
   boxLayout->addWidget(gearBox, 1, 2);
   boxLayout->addWidget(engineRuntimeBox, 1, 2);
   boxLayout->addWidget(engineLoadBox, 1, 2);
   boxLayout->addWidget(fuelPressureBox, 1, 2);
   boxLayout->addWidget(accBox, 1, 2);

   boxLayout->setColumnMinimumWidth(3, 75);
   boxLayout->setColumnMinimumWidth(5, 30);
   for (int i=0; i<5; i++)
   {
      boxLayout->setColumnStretch(i, 1);
   }

   boxLayout->addWidget(m_logButton, 2, 1);

   m_CANWarning = new QLabel(this);
   m_CANWarning->setText("ODB2 not connected");
   m_CANWarning->hide();

   m_warningTimer = new QTimer(this);
   connect(m_warningTimer, SIGNAL(timeout()), this, SLOT(WarningTimeout()));
   //m_CANWarning->show();

   boxLayout->addWidget(m_CANWarning, 3, 1);

   currentRightChannel.box = airTempBox;
   currentRightChannel.obj = m_airTempObject;
   currentLeftChannel.box = speedBox;
   currentLeftChannel.obj = m_speedObject;
   currentLeftChannel.num = m_engineRuntimeLCD;
   currentRightChannel.num = m_engineRuntimeLCD;

   /* default hidden gauges */
   rpmBox->hide();
   accBox->hide();
   throttleBox->hide();
   gearBox->hide();
   fuelPressureBox->hide();
   engineLoadBox->hide();
   engineRuntimeBox->hide();

   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);

   setLayout(vLayout); 

   m_warningTimer->start(1000);
}

void Diagnostics::WarningTimeout()
{
   qDebug() << "TIMEOUT";
   if (m_timedout) 
   {
      m_CANWarning->show();
      m_timedout = false;
   }
   else 
   {
      m_CANWarning->hide();
      m_timedout = true;
   }
   
}

void Diagnostics::EnableButtons()
{
   m_intakeAirTempButton->setEnabled(true);
   m_speedButton->setEnabled(true);
   m_gearButton->setEnabled(true);
   m_fuelPressureButton->setEnabled(true);
   m_engineRuntimeButton->setEnabled(true);
   m_throttleButton->setEnabled(true);
   m_speedButton->setEnabled(true);
   m_rpmButton->setEnabled(true);
   m_engineLoadButton->setEnabled(true);
}

void Diagnostics::DiagDataRx(diagMsg_t* msg)
{
   if (msg->connectionFault == true)
   {
      
      if(canConnectionFlag == true)
      {
         m_speedObject->setProperty("myVal", 0);
         canConnectionFlag = false; 
      }    
   }
   else 
   {
      if(canConnectionFlag == false)
      {
         cout<<"CAN bus connection established"<<endl;
         m_warningTimer->stop();
         m_CANWarning->hide();
         canConnectionFlag = true;
      }
       
      int leftVal;
      int rightVal;

      /* scale rpm down by factor of 100 */
      if (currentLeftChannel.obj == m_rpmObject) { leftVal = (msg->channelA) / 100; }
      else { leftVal = msg->channelA; }
      //leftVal = msg->channelA;
      rightVal = msg->channelB;
      
      currentLeftChannel.obj->setProperty("value", leftVal);
      currentLeftChannel.num->display(leftVal);

      if (currentRightGauge != accBox)
      {
         currentRightChannel.obj->setProperty("value", rightVal);
         //currentRightChannel.obj->setProperty("value", 15);
         currentRightChannel.num->display(msg->channelB);
      }
           
   }
   
}

void Diagnostics::AccDataRx(accValues_t* msg)
{
   m_accGauge->update_gauge(msg);
}

void Diagnostics::ConnectButtons()
{
   connect(m_rpmButton, SIGNAL (clicked()), this, SLOT (ShowRpmGauge()));
   connect(m_speedButton, SIGNAL (clicked()), this, SLOT (ShowSpeedGauge()));
   connect(m_intakeAirTempButton, SIGNAL (clicked()), this, SLOT (ShowAirTempGauge()));
   connect(m_throttleButton, SIGNAL (clicked()), this, SLOT (ShowThrottleGauge()));
   connect(m_gearButton, SIGNAL (clicked()), this, SLOT (ShowGearGauge()));
   connect(m_fuelPressureButton, SIGNAL (clicked()), this, SLOT (ShowFuelPressureGauge()));
   connect(m_engineRuntimeButton, SIGNAL (clicked()), this, SLOT (ShowEngineRuntimeGauge()));
   connect(m_engineLoadButton, SIGNAL (clicked()), this, SLOT (ShowEngineLoadGauge()));
   connect(m_accButton, SIGNAL (clicked()), this, SLOT (ShowAccGauge()));
   
   connect(m_logButton, SIGNAL (clicked()), this, SLOT (JourneyLogRequest()));
   connect(m_logWindow, SIGNAL (LogRequestTx(QVector<QString>, bool)), this, SLOT (LogRequestRx(QVector<QString>, bool)));
   connect(m_logWindow, SIGNAL (CloseRequest()), this, SLOT (CloseLogWindow()));

}

/* public slots */

void Diagnostics::ShowAccGauge()
{
   if (currentRightGauge != accBox)
   {
      currentRightChannel.box->hide();
      accBox->show();
      currentRightChannel.box = accBox;
   }
   
}

void Diagnostics::ShowAirTempGauge()
{
   if (currentRightGauge != airTempBox)
   {
      /* request intake air temperate to be obtained from the OBD2 thread */
      emit NewChannelRequest(AIR_TEMP, CHANNEL_A);
      currentRightChannel.box->hide();
      airTempBox->show();
      currentRightChannel.box = airTempBox;
      currentRightChannel.num = m_airTempLCD;
      currentRightChannel.obj = m_airTempObject;
   }
}

void Diagnostics::ShowSpeedGauge()
{
   if (currentRightGauge != speedBox)
   {
      /* request speed data to be obtained from the OBD2 thread */
      emit NewChannelRequest(SPEED, CHANNEL_A);
      currentLeftChannel.box->hide();
      speedBox->show();
      currentLeftChannel.box = speedBox; 
      currentLeftChannel.num = m_speedLCD;
      currentLeftChannel.obj = m_speedObject;

   }
}

void Diagnostics::ShowRpmGauge()
{
   if (currentLeftGauge != rpmBox)
   {
      /* request RPM data to be obtained from the OBD2 thread */
      emit NewChannelRequest(RPM, CHANNEL_A);
      currentLeftChannel.box->hide();
      rpmBox->show();
      currentLeftChannel.box = rpmBox;
      currentLeftChannel.num = m_rpmLCD;
      currentLeftChannel.obj = m_rpmObject;
   }     
}

void Diagnostics::ShowThrottleGauge()
{
   if (currentRightGauge != throttleBox)
   {
      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(THROTTLE, CHANNEL_A);
      currentLeftChannel.box->hide();
      throttleBox->show();
      currentLeftChannel.box = throttleBox;
      currentLeftChannel.num = m_throttleLCD;
      currentLeftChannel.obj = m_throttleObject;
   }  
}

void Diagnostics::ShowGearGauge()
{
   if (currentRightGauge != gearBox)
   {
      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(GEAR, CHANNEL_B);
      currentRightChannel.box->hide();
      gearBox->show();
      currentRightChannel.box = gearBox;
      currentRightChannel.num = m_gearLCD;
      currentRightChannel.obj = m_gearObject;
   } 
}

void Diagnostics::ShowFuelPressureGauge()
{
   if (currentRightGauge != fuelPressureBox)
   {
      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(FUEL_PRESSURE, CHANNEL_B);
      currentRightChannel.box->hide();
      fuelPressureBox->show();
      currentRightChannel.box = fuelPressureBox;
      currentRightChannel.num = m_fuelPressureLCD;
      currentRightChannel.obj = m_fuelPressureObject;
   } 

}

void Diagnostics::ShowEngineRuntimeGauge()
{
   if (currentRightGauge != engineRuntimeBox)
   {
      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(ENGINE_RUNTIME, CHANNEL_B);
      currentRightChannel.box->hide();
      engineRuntimeBox->show();
      currentRightChannel.box = engineRuntimeBox;
      currentRightChannel.num = m_engineRuntimeLCD;
      currentRightChannel.obj = m_engineRuntimeObject;
   } 
}

void Diagnostics::ShowEngineLoadGauge()
{
   if (currentRightGauge != engineLoadBox)
   {
      /* request throttle data to be obtained from the OBD2 thread */
      emit NewChannelRequest(ENGINE_LOAD, CHANNEL_B);
      currentRightChannel.box->hide();
      engineLoadBox->show();
      currentRightChannel.box = engineLoadBox;
      currentRightChannel.num = m_engineLoadLCD;
      currentRightChannel.obj = m_engineLoadObject;
   } 
}

void Diagnostics::JourneyLogRequest()
{
   cout<<"LOG REQUESTED"<<endl;

   
   //m_logWindow = new LoggerWindow(obd->supported_pids);
   if(!m_logWindow->isHidden())
   {
      m_logWindow->raise();
   }
   else
   {
      m_logWindow->reset();
      m_logWindow->show();
      ButtonState(false);
   }
   /* TODO: implement log request signal*/
   /* send log request to state machine */
   //emit StartLogging();
}

void Diagnostics::LogRequestRx(QVector<QString> logParams, bool start)
{
   qDebug() << "DIAGNOSTICS: ";
   for (int i = 0; i < logParams.size(); i++)
   {
      qDebug() << logParams[i];
   }

   if (start == false)
   {
      //m_logWindow->hide();
      m_logButton->setEnabled(true);
   }
   
   emit StartLogging(logParams, start);
}
void Diagnostics::CloseLogWindow()
{
   m_logWindow->hide();
   m_logButton->setEnabled(true);
   m_logWindow->reset();
   ButtonState(true);
}

void Diagnostics::StateChangeMainMenu()
{
   qDebug() << "clicked home button";
   emit DisplayChange(MAIN_MENU, this);
}

void Diagnostics::ShowMe()
{
   this->show();
   if (m_logWindow->isLogging()) m_logWindow->raise();
}

void Diagnostics::ButtonState(bool state)
{
   for (int count = 0; count < obd->supported_pids.size(); count++)
   {
      switch (Hash::HashPID(obd->supported_pids[count])) // JB: fixed bug here (13/03/19)
      {
         /* fast channel buttons */
         case ENGINE_LOAD :      m_engineLoadButton->setEnabled(state);
                                 break;
         case RPM :              m_rpmButton->setEnabled(state);
                                 break;
         case SPEED :            m_speedButton->setEnabled(state);
                                 break;
         case THROTTLE :         m_throttleButton->setEnabled(state);
                                 break;
         case ENGINE_RUNTIME :   m_engineRuntimeButton->setEnabled(state);
                                 break;
         /* slow channel buttons */
         case FUEL_PRESSURE :    m_fuelPressureButton->setEnabled(state);
                                 break;
         case AIR_TEMP :         m_intakeAirTempButton->setEnabled(state);
                                 break;
         case GEAR :             m_gearButton->setEnabled(state);
                                 break;
         default :               break;
      }
   }
   m_accButton->setEnabled(state);
}