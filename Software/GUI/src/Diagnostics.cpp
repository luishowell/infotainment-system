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
#include <QStackedLayout>
#include <QGroupBox>
#include <QDial>
#include <Qt>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlProperty>

#include <vector>
#include <string>

//#include <stdio.h>
#include <iostream>
#include "Diagnostics.h" 
#include "config.h"
#include "Hash.h"


using namespace std;

/**
 * @brief Construct a new Diagnostics:: Diagnostics object
 * 
 * @param parent 
 */
Diagnostics::Diagnostics(QWidget *parent) : QWidget(parent) 
 {   

   QVector<QString> testVec;
   testVec.push_back("0C");
   testVec.push_back("0D");
   testVec.push_back("0F");
   testVec.push_back("11");
   testVec.push_back("1F");
   testVec.push_back("04");
   testVec.push_back("A4");
   testVec.push_back("0A");

   m_logWindow = new LoggerWindow(testVec);
   //connect(m_logWindow, SIGNAL (LogRequestTx(std::vector<std::string>)), this, SLOT (JourneyLogRequest(std::vector<std::string>))); 



   setFixedSize(widgetSize);
   CreateComponents();
   //CreateLayout();    
   
   connect(this, SIGNAL (NewChannelRequest(diagParams_t, obd2Channel_t)), parent, SLOT (OnNewChannelRequest(diagParams_t, obd2Channel_t))); 

   ConnectButtons();
   //connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 

   /* CAN bus initially assumed disconnected until the CAN thread specifies no connection fault */
   canConnectionFlag = false;

   //logClicked = 0;

   qRegisterMetaType<diagParams_t>("diagParams_t");
   qRegisterMetaType<obd2Channel_t>("obd2Channel_t");

 }

/**
 * @brief 
 * 
 */
void Diagnostics::CreateComponents()
{
   qDebug() << "DIAGNOSTICS: creating components";
   const QSize gaugeSize = QSize(100, 175);
   const QSize dialSize = QSize(170, 125);

   /* set up speedometer */
   QQuickView *speedoQML = new QQuickView();
   m_speedometer = QWidget::createWindowContainer(speedoQML, this);  
   m_speedometer->setFixedSize(dialSize);
   speedoQML->setSource(QUrl::fromLocalFile("../GUI/src/Speedometer.qml"));
   speedoQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_speedObject = speedoQML->rootObject();

   /* set up RPM gauge */
   QQuickView *rpmQML = new QQuickView();
   m_rpmGauge = QWidget::createWindowContainer(rpmQML, this);  
   m_rpmGauge->setFixedSize(dialSize);
   rpmQML->setSource(QUrl::fromLocalFile("../GUI/src/RpmGauge.qml"));
   rpmQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_rpmObject = rpmQML->rootObject();

   /* set up intake air temperature gauge */
   QQuickView *airTempQML = new QQuickView();
   m_airTempGauge = QWidget::createWindowContainer(airTempQML, this);  
   m_airTempGauge->setFixedSize(gaugeSize);
   airTempQML->setSource(QUrl::fromLocalFile("../GUI/src/AirTempGauge.qml"));
   airTempQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_airTempObject = airTempQML->rootObject();

   /* set up throttle gauge */
   QQuickView *throttleQML = new QQuickView();
   m_throttleGauge = QWidget::createWindowContainer(throttleQML, this);  
   m_throttleGauge->setFixedSize(gaugeSize);
   throttleQML->setSource(QUrl::fromLocalFile("../GUI/src/ThrottleGauge.qml"));
   throttleQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_throttleObject = throttleQML->rootObject();

   /* set up gear gauge */
   QQuickView *gearQML = new QQuickView();
   m_gearGauge = QWidget::createWindowContainer(gearQML, this);  
   m_gearGauge->setFixedSize(gaugeSize);
   gearQML->setSource(QUrl::fromLocalFile("../GUI/src/ThrottleGauge.qml"));
   gearQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_gearObject = gearQML->rootObject();

   /* set up fuel pressure gauge */
   QQuickView *fuelPressureQML = new QQuickView();
   m_fuelPressureGauge = QWidget::createWindowContainer(fuelPressureQML, this);  
   m_fuelPressureGauge->setFixedSize(gaugeSize);
   fuelPressureQML->setSource(QUrl::fromLocalFile("../GUI/src/FuelPressureGauge.qml"));
   fuelPressureQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_fuelPressureObject = fuelPressureQML->rootObject();

   /* set up engine runtime gauge */
   QQuickView *engineRuntimeQML = new QQuickView();
   m_engineRuntimeGauge = QWidget::createWindowContainer(engineRuntimeQML, this);  
   m_engineRuntimeGauge->setFixedSize(gaugeSize);
   engineRuntimeQML->setSource(QUrl::fromLocalFile("../GUI/src/ThrottleGauge.qml"));
   engineRuntimeQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_engineRuntimeObject = engineRuntimeQML->rootObject();
  
   /* set up engine load gauge */
   QQuickView *engineLoadQML = new QQuickView();
   m_engineLoadGauge = QWidget::createWindowContainer(engineLoadQML, this);  
   m_engineLoadGauge->setFixedSize(gaugeSize);
   engineLoadQML->setSource(QUrl::fromLocalFile("../GUI/src/EngineLoadGauge.qml"));
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

   const QSize btnSize = QSize(120, 50);
   m_rpmButton->setFixedSize(btnSize);
   m_speedButton->setFixedSize(btnSize);
   m_intakeAirTempButton->setFixedSize(btnSize);
   m_throttleButton->setFixedSize(btnSize);
   m_throttleButton->setFixedSize(btnSize);
   m_engineRuntimeButton->setFixedSize(btnSize);
   m_engineLoadButton->setFixedSize(btnSize);
   m_gearButton->setFixedSize(btnSize);
   m_fuelPressureButton->setFixedSize(btnSize);
   
   m_logButton = new QPushButton("Log Journey");
   m_logButton->setFixedSize(400, 50);
}

/**
 * @brief 
 * 
 */
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
   speedBox = new QGroupBox("Speed", titleBox);
   m_speedLCD = new QLCDNumber();
   speedBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *speedLayout = new QVBoxLayout(speedBox);
   speedLayout->addWidget(m_speedometer);
   speedLayout->addWidget(m_speedLCD);

   rpmBox = new QGroupBox("RPM", titleBox);
   m_rpmLCD = new QLCDNumber();
   rpmBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *rpmLayout = new QVBoxLayout(rpmBox);
   rpmLayout->addWidget(m_rpmGauge);
   rpmLayout->addWidget(m_rpmLCD);

   airTempBox = new QGroupBox("Intake Air Temperature", titleBox);
   m_airTempLCD = new QLCDNumber();
   airTempBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *airTempLayout = new QHBoxLayout(airTempBox);
   airTempLayout->addWidget(m_airTempGauge);
   airTempLayout->addWidget(m_airTempLCD);

   throttleBox = new QGroupBox("Throttle Position", titleBox);
   m_throttleLCD = new QLCDNumber();
   throttleBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *throttleLayout = new QHBoxLayout(throttleBox);
   throttleLayout->addWidget(m_throttleGauge);
   throttleLayout->addWidget(m_throttleLCD);

   gearBox = new QGroupBox("Current Gear", titleBox);
   m_gearLCD = new QLCDNumber();
   gearBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *gearLayout = new QStackedLayout(gearBox);
   gearLayout->addWidget(m_gearLCD);
   gearLayout->addWidget(m_gearGauge);
   
 
   fuelPressureBox = new QGroupBox("Fuel Pressure", titleBox);
   m_fuelPressureLCD = new QLCDNumber();
   fuelPressureBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *fuelPressureLayout = new QHBoxLayout(fuelPressureBox);
   fuelPressureLayout->addWidget(m_fuelPressureGauge);
   fuelPressureLayout->addWidget(m_fuelPressureLCD);
   
   engineRuntimeBox = new QGroupBox("Engine Runtime", titleBox);
   m_engineRuntimeLCD = new QLCDNumber(engineRuntimeBox);
   engineRuntimeBox->setAlignment(Qt::AlignHCenter);
   QStackedLayout *engineRuntimeLayout = new QStackedLayout(engineRuntimeBox);
   engineRuntimeLayout->addWidget(m_engineRuntimeLCD); 
   engineRuntimeLayout->addWidget(m_engineRuntimeGauge); //JB: without this loads of random white space?? 

   engineLoadBox = new QGroupBox("Engine Load", titleBox);
   m_engineLoadLCD = new QLCDNumber();
   engineLoadBox->setAlignment(Qt::AlignHCenter);
   QHBoxLayout *engineLoadLayout = new QHBoxLayout(engineLoadBox);
   engineLoadLayout->addWidget(m_engineLoadGauge);  
   engineLoadLayout->addWidget(m_engineLoadLCD);  

   /* parameter selection box */
   selectBox = new QGroupBox("Parameters", titleBox);
   selectBox->setAlignment(Qt::AlignHCenter);
   selectBox->setFixedSize(250, 250);
   QHBoxLayout *selectLayout = new QHBoxLayout(selectBox);
   QVBoxLayout *selectLeft = new QVBoxLayout(selectBox);
   QVBoxLayout *selectRight = new QVBoxLayout(selectBox);

   #ifndef GUI_TEST
   /* only add selection buttons for the supported obd2 pids */
   QString QPid;
   pidNum = obd->supported_pids.size();
   for (pidCnt = 0; pidCnt < pidNum; pidCnt++)
   {
      QPid = QString::fromUtf8(obd->supported_pids[pidNum].c_str());
      switch (Hash::HashPID(QPid))
      {
         /* fast channel buttons */
         case ENGINE_LOAD :      selectLeft->addWidget(m_engineLoadButton);
                                 break;
         case RPM :              selectLeft->addWidget(m_rpmButton);
                                 break;
         case SPEED :            selectLeft->addWidget(m_speedButton);
                                 break;
         case THROTTLE :         selectLeft->addWidget(m_throttleButton);
                                 break;
         case ENGINE_RUNTIME :   selectLeft->addWidget(m_engineRuntimeButton);
                                 break;
         /* slow channel buttons */
         case FUEL_PRESSURE :    selectRight->addWidget(m_fuelPressureButton);
                                 break;
         case AIR_TEMP :         selectRight->addWidget(m_intakeAirTempButton);
                                 break;
         case GEAR :             selectRight->addWidget(m_gearButton);
                                 break;
         default :               break;
      }
   }
   #else
   vector<string> supported_pids;
   supported_pids.push_back("0D");
   supported_pids.push_back("0C");
   supported_pids.push_back("11");
   supported_pids.push_back("0F");
   supported_pids.push_back("A4");
   supported_pids.push_back("1F");

   
   int num = supported_pids.size();
   int cnt;
   for (cnt = 0; cnt < num; cnt++)
   {
      cout << supported_pids[cnt] << endl;;
      switch (Hash::HashPID(supported_pids[cnt]))
      {
         /* fast channel buttons */
         case ENGINE_LOAD :      selectLeft->addWidget(m_engineLoadButton);
                                 break;
         case RPM :              selectLeft->addWidget(m_rpmButton);
                                 break;
         case SPEED :            selectLeft->addWidget(m_speedButton);
                                 break;
         case THROTTLE :         selectLeft->addWidget(m_throttleButton);
                                 break;
         /* slow channel buttons */
         case FUEL_PRESSURE :    selectRight->addWidget(m_fuelPressureButton);
                                 break;
         case AIR_TEMP :         selectRight->addWidget(m_intakeAirTempButton);
                                 break;
         case GEAR :             selectRight->addWidget(m_gearButton);
                                 break;
         case ENGINE_RUNTIME :   selectRight->addWidget(m_engineRuntimeButton);
                                 break;
         default :               break;
      }
   }
   #endif

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
   titleBox->setFixedSize(WIDGET_SIZE_X-30, WIDGET_SIZE_Y-100);

   /* default shown gauges */
   boxLayout->addWidget(selectBox, 1, 3);
   boxLayout->addWidget(speedBox, 1, 1);
   boxLayout->addWidget(rpmBox, 1, 1);
   boxLayout->addWidget(throttleBox, 1, 1);
   boxLayout->addWidget(airTempBox, 1, 2);
   boxLayout->addWidget(gearBox, 1, 2);
   boxLayout->addWidget(engineRuntimeBox, 1, 2);
   boxLayout->addWidget(engineLoadBox, 1, 2);
   boxLayout->addWidget(fuelPressureBox, 1, 2);

   boxLayout->addWidget(m_logButton, 2, 1);
   //boxLayout->addWidget(m_engineRuntimeLCD, 1, 4);
   

/*
   currentRightGauge = speedBox;
   m_currentRightObj = m_speedObject;
   currentLeftGauge = rpmBox;
   m_currentLeftObj = m_rpmObject;
*/

   currentRightChannel.box = airTempBox;
   currentRightChannel.obj = m_airTempObject;
   currentLeftChannel.box = speedBox;
   currentLeftChannel.obj = m_speedObject;
   currentLeftChannel.num = m_engineRuntimeLCD;
   currentRightChannel.num = m_engineRuntimeLCD;

   /* default hidden gauges */
   rpmBox->hide();
   //airTempBox->hide();
   throttleBox->hide();
   gearBox->hide();
   fuelPressureBox->hide();
   engineLoadBox->hide();
   engineRuntimeBox->hide();

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
      //cout<<"WARNING: no connection to CAN bus"<<endl;

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
      //cout<<"A:"<< msg->channelA << endl;
      //cout<<"B:"<< msg->channelB <<endl;
      //cout<<"/****************/"<<endl;
      int leftVal;
      int rightVal;

      /* scale rpm down by factor of 100 */
      if (currentLeftChannel.obj == m_rpmObject) { leftVal = (msg->channelA) / 100; }
      else { leftVal = msg->channelA; }
      //leftVal = msg->channelA;
      rightVal = msg->channelB;
      
      currentLeftChannel.obj->setProperty("value", leftVal);
      currentRightChannel.obj->setProperty("value", rightVal);
      currentLeftChannel.num->display(leftVal);
      currentRightChannel.num->display(msg->channelB);
      
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
   connect(m_gearButton, SIGNAL (clicked()), this, SLOT (ShowGearGauge()));
   connect(m_fuelPressureButton, SIGNAL (clicked()), this, SLOT (ShowFuelPressureGauge()));
   connect(m_engineRuntimeButton, SIGNAL (clicked()), this, SLOT (ShowEngineRuntimeGauge()));
   connect(m_engineLoadButton, SIGNAL (clicked()), this, SLOT (ShowEngineLoadGauge()));
   
   connect(m_logButton, SIGNAL (clicked()), this, SLOT (JourneyLogRequest()));
   connect(m_logWindow, SIGNAL (LogRequestTx(QVector<QString>)), this, SLOT (LogRequestRx(QVector<QString>)));

   //connect(m_logButton, &QPushButton::clicked, this, &Diagnostics::JourneyLogRequest);

}

/* public slots */
/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
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

/**
 * @brief 
 * 
 */
void Diagnostics::JourneyLogRequest()
{
   cout<<"LOG REQUESTED"<<endl;

   
   //m_logWindow = new LoggerWindow(obd->supported_pids);

   m_logWindow->show();

   /* TODO: implement log request signal*/
   /* send log request to state machine */
   //emit StartLogging();
}

/**
 * @brief 
 * 
 * @param logParams 
 */
void Diagnostics::LogRequestRx(QVector<QString> logParams)
{
   qDebug() << "DIAGNOSTICS: ";
   for (int i = 0; i < logParams.size(); i++)
   {
      qDebug() << logParams[i];
   }
   
   emit StartLogging(logParams);
}


/**
 * @brief 
 * 
 */
void Diagnostics::StateChangeMainMenu()
{
   qDebug() << "clicked home button";
   emit DisplayChange(MAIN_MENU, this);
}