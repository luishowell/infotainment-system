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

#include <stdio.h>
#include "Diagnostics.h" 
#include "config.h"


Diagnostics::Diagnostics(QWidget *parent) : QWidget(parent) 
 {   
   setFixedSize(widgetSize);
   CreateComponents();
   CreateLayout();    
   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 

   /* CAN bus initially assumed disconnected until the CAN thread specifies no connection fault */
   canConnectionFlag = false;
 }


void Diagnostics::CreateComponents()
{
   /* set up speedometer */
   QQuickView *speedoQML = new QQuickView();
   m_speedometer = QWidget::createWindowContainer(speedoQML, this);  
   m_speedometer->setFixedSize(175, 175);
   speedoQML->setSource(QUrl::fromLocalFile("../../../../src/Speedometer.qml"));
   speedoQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_speedObject = speedoQML->rootObject();

   /* set up RPM gauge */
   QQuickView *rpmQML = new QQuickView();
   m_rpmGauge = QWidget::createWindowContainer(rpmQML, this);  
   m_rpmGauge->setFixedSize(175, 175);
   rpmQML->setSource(QUrl::fromLocalFile("../../../../src/RpmGauge.qml"));
   rpmQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_rpmObject = rpmQML->rootObject();

   /* set up fuel gauge */
   QQuickView *fuelQML = new QQuickView();
   m_fuelGauge = QWidget::createWindowContainer(fuelQML, this);  
   m_fuelGauge->setFixedSize(100, 175);
   fuelQML->setSource(QUrl::fromLocalFile("../../../../src/FuelGauge.qml"));
   fuelQML->setResizeMode(QQuickView::SizeRootObjectToView);
   m_fuelObject = fuelQML->rootObject();
}

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
   QGroupBox* speedBox = new QGroupBox("Speed", titleBox);
   speedBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *speedLayout = new QVBoxLayout(speedBox);
   speedLayout->addWidget(m_speedometer);

   QGroupBox* rpmBox = new QGroupBox("RPM", titleBox);
   rpmBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *rpmLayout = new QVBoxLayout(rpmBox);
   rpmLayout->addWidget(m_rpmGauge);

   QGroupBox* fuelBox = new QGroupBox("Fuel", titleBox);
   fuelBox->setAlignment(Qt::AlignHCenter);
   QVBoxLayout *fuelLayout = new QVBoxLayout(fuelBox);
   fuelLayout->addWidget(m_fuelGauge);
   

   

   fuelBox->setFixedSize(130,220);
   speedBox->setFixedSize(200,225);
   rpmBox->setFixedSize(200,225);
   titleBox->setFixedSize(WIDGET_SIZE_X-30, WIDGET_SIZE_Y-100);

   boxLayout->addWidget(speedBox, 1, 1);
   boxLayout->addWidget(rpmBox, 1, 2);
   boxLayout->addWidget(fuelBox, 1, 3);

   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);

   setLayout(vLayout);

}

void Diagnostics::DiagDataRx(diagMsg_t* msg)
{
   if (msg->connectionFault == true)
   {
      printf("WARNING: no connection to CAN bus\n");

      if(canConnectionFlag == true)
      {
         //m_speedDial->setValue(0);
         //m_speedSlider->setValue(0);
         //m_fuelGauge->setValue(0);

         canConnectionFlag = false; 
      }    
   }
   else 
   {
      if(canConnectionFlag == false)
      {
         printf("CAN bus connection established\n");
         canConnectionFlag = true;
      }
      printf("/******DIAG******/\n");
      printf("Speed: %d\n", msg->speed);
      printf("RPM: %d\n", msg->rpm);
      printf("Fuel: %d\n", msg->fuel);
      printf("/****************/\n");

      //m_speedDial->setValue(msg->speed);
      //m_speedSlider->setValue(msg->rpm);
      //speedObject->setProperty("value", msg->speed);
      //QQmlProperty(speedo, "value").write(msg->speed);

      m_speedObject->setProperty("value", msg->speed);
      m_rpmObject->setProperty("value", msg->rpm);
      m_fuelObject->setProperty("value", msg->fuel);
   }
   
}

void Diagnostics::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}