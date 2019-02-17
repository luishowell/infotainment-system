/**
 * @file MainMenu.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "MainMenu.h" 
#include <QApplication>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <Qt>
#include "config.h"

/**
 * @brief Construct a new Main Menu:: Main Menu object
 * 
 * @param parent 
 */
MainMenu::MainMenu(QWidget *parent) : QWidget(parent) 
 {
   setFixedSize(widgetSize);

   CreateLayout();    

   /* connect buttons to state request signal emits  */
   connect(m_diagButton, SIGNAL (clicked()), this, SLOT (StateChangeDiag()));
   connect(m_mediaButton, SIGNAL (clicked()), this, SLOT (StateChangeMedia()));
   connect(m_parkButton, SIGNAL (clicked()), this, SLOT (StateChangeParking()));
   connect(m_errorButton, SIGNAL (clicked()), this, SLOT (StateChangeErrorCodes()));
 }

/**
 * @brief 
 * 
 */
void MainMenu::CreateLayout()
{
   QVBoxLayout* vLayout = new QVBoxLayout(this);
   QGroupBox* titleBox = new QGroupBox("Main Menu", this);

   /* create buttons */
   m_diagButton = new QPushButton("Diagnostics");
   m_mediaButton = new QPushButton("Media");
   m_parkButton = new QPushButton("Parking Mode");
   m_errorButton = new QPushButton("Error Codes");

   const QSize btnSize = QSize(200, 140);
   m_diagButton->setFixedSize(btnSize);
   m_mediaButton->setFixedSize(btnSize);
   m_parkButton->setFixedSize(btnSize);
   m_errorButton->setFixedSize(btnSize);

   /* set layout */
   QGridLayout* layout = new QGridLayout(titleBox);
   layout->addWidget(m_diagButton, 0, 0, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_mediaButton, 0, 20, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_parkButton, 4, 0, 5, 2, Qt::AlignHCenter);
   layout->addWidget(m_errorButton, 4, 20, 5, 2, Qt::AlignHCenter);
   layout->setAlignment(Qt::AlignHCenter);

   
   titleBox->setFixedSize(WIDGET_SIZE_X-30, 380);
   
   titleBox->setLayout(layout);
   
   vLayout->addWidget(titleBox);
   titleBox->setAlignment(Qt::AlignHCenter);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeDiag()
{
   emit DisplayChange(DIAGNOSTICS, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeParking()
{
   emit DisplayChange(PARKING, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeErrorCodes()
{
   emit DisplayChange(ERROR_CODES, this);
}

/**
 * @brief 
 * 
 */
void MainMenu::StateChangeMedia()
{
   emit DisplayChange(MEDIA, this);
}