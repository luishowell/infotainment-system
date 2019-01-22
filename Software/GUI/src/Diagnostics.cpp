#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QDial>
#include <Qt>
#include <stdio.h>
#include "Diagnostics.h" 
#include "config.h"


Diagnostics::Diagnostics(QWidget *parent) : QWidget(parent) 
 {   
   setFixedSize(widgetSize);
   CreateLayout();    
   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 

   /* CAN bus initially assumed disconnected until the CAN thread specifies no connection fault */
   canConnectionFlag = false;
 }

void Diagnostics::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);

   QGroupBox* titleBox = new QGroupBox("Diagnostics", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);
   //QGridLayout* boxLayout = new QGridLayout(speedBox);

   boxLayout->setVerticalSpacing(10);

   /* speed meter has range up to 200mph */
   m_speedSlider = new QSlider(Qt::Horizontal);
   m_speedSlider->setRange(0, 200);
   m_speedSlider->setFixedSize(WIDGET_SIZE_X-400, 50);

   m_fuelGauge = new QSlider(Qt::Vertical);
   m_fuelGauge->setRange(0, 100);
   m_fuelGauge->setFixedSize(WIDGET_SIZE_X-500, 50);

   m_speedDial = new QDial();
   m_speedDial->setRange(0, 200);
   m_speedDial->setFixedSize(WIDGET_SIZE_X-300, 50);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   
   boxLayout->addWidget(m_speedSlider,20, 0, 0, 5);
   boxLayout->addWidget(m_fuelGauge, 20, 5, 0, 5);
   boxLayout->addWidget(m_speedDial, 17, 0, 5, 5);


   //speedBox->setFixedSize(WIDGET_SIZE_X-300,100);
   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
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
         m_speedDial->setValue(0);
         m_speedSlider->setValue(0);
         m_fuelGauge->setValue(0);

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

      m_speedDial->setValue(msg->speed);
      m_speedSlider->setValue(msg->rpm);
   }
   
}

void Diagnostics::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}