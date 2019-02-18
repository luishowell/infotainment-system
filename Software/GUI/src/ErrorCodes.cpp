/**
 * @file ErrorCodes.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include "ErrorCodes.h" 
#include "config.h"

/**
 * @brief Construct a new Error Codes:: Error Codes object
 * 
 * @param parent 
 */
ErrorCodes::ErrorCodes(QWidget *parent) : QWidget(parent) 
 {
     
    setFixedSize(widgetSize);

   CreateLayout();    

    connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));
    
 }

/**
 * @brief 
 * 
 */
void ErrorCodes::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

/**
 * @brief 
 * 
 */
void ErrorCodes::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);
   
   QGroupBox* titleBox = new QGroupBox("Error Codes", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);
   boxLayout->setVerticalSpacing(10);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}
