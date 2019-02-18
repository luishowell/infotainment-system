/**
 * @file Media.cpp
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
#include "Media.h" 
#include "config.h"

/**
 * @brief Construct a new Media:: Media object
 * 
 * @param parent 
 */
Media::Media(QWidget *parent) : QWidget(parent) 
 {
     
    setFixedSize(widgetSize);

    CreateLayout();    

    connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));
    
 }

/**
 * @brief 
 * 
 */
void Media::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

/**
 * @brief 
 * 
 */
void Media::CreateLayout()
{
    QVBoxLayout* vLayout = new QVBoxLayout(this);
   vLayout->setSpacing(25);
   
   QGroupBox* titleBox = new QGroupBox("Media", this);
   titleBox->setAlignment(Qt::AlignHCenter);

   QGridLayout* boxLayout = new QGridLayout(titleBox);
   boxLayout->setVerticalSpacing(10);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);
   

   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}
