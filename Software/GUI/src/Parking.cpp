 #include <QApplication>
 #include <QGridLayout>
 #include <QGroupBox>
 #include "Parking.h"
 #include "config.h"

Parking::Parking(QWidget *parent) : QWidget(parent) 
 {
     
   setFixedSize(widgetSize);

   CreateLayout();    

   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));
    
 }

void Parking::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

void Parking::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);
   
   QGroupBox* titleBox = new QGroupBox("Parking Mode", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);
   boxLayout->setVerticalSpacing(10);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);

}
