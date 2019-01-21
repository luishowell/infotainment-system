#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QDial>
#include <Qt>
#include "Diagnostics.h" 
#include "config.h"


Diagnostics::Diagnostics(QWidget *parent) : QWidget(parent) 
 {   
   setFixedSize(widgetSize);
   CreateLayout();    
   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu())); 
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

   m_speedDial = new QDial();
   m_speedDial->setRange(0, 200);
   m_speedDial->setFixedSize(WIDGET_SIZE_X-300, 50);


   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   
   boxLayout->addWidget(m_speedSlider,20, 0, 0, 5);
   boxLayout->addWidget(m_speedDial, 17, 0, 5, 5);



   //speedBox->setFixedSize(WIDGET_SIZE_X-300,100);
   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);

   setLayout(vLayout);

}

void Diagnostics::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}