/**
 * @file ErrorCodes.cpp
 * @author Luis Howell
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "ErrorCodes.h" 
#include "config.h"
#include "Mutex.h"

#include <QtCore>
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <iostream>
#include <unistd.h>

/**
 * @brief Construct a new Error Codes:: Error Codes object
 * 
 * @param parent 
 */
ErrorCodes::ErrorCodes(QWidget *parent, obd2* myObd) : QWidget(parent) 
{
   obd = myObd;
      
   setFixedSize(widgetSize);

   CreateLayout();    

   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));    
   connect(getButton, SIGNAL (clicked()), this, SLOT (GetErrorCodes()));
   connect(clearButton, SIGNAL (clicked()), this, SLOT (ClearErrorCodes()));
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

   QGridLayout *gridLayout = new QGridLayout;
   gridLayout->setVerticalSpacing(20);

   m_homeButton = new QPushButton("Home");
   m_homeButton->setFixedSize(WIDGET_SIZE_X-30, 50);

   errorTable = new QTableWidget(7, 2, this);
   errorTable->horizontalHeader()->setStretchLastSection(true);
   errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);   //prevent table editing
   errorTable->setHorizontalHeaderLabels(QStringList() << "Error Code" << "Description");

   getButton = new QPushButton("Get Error Codes");
   clearButton = new QPushButton("Clear Error Codes");   

   gridLayout->addWidget(errorTable, 0, 0, 4, 1);
   gridLayout->addWidget(getButton,0,1,2,1);
   gridLayout->addWidget(clearButton,2,1,2,1);

   titleBox->setLayout(gridLayout);   
   titleBox->setFixedSize(WIDGET_SIZE_X-30, 300);
   vLayout->addWidget(titleBox);
   vLayout->addWidget(m_homeButton, Qt::AlignBottom);
}

/* TODO: move the OBD2 call  */
void ErrorCodes::GetErrorCodes()
{
   bool waiting = true;
   bool notifyFlag = true; 

   //qDebug() << "ERROR CODES: clicked";
   while (waiting)
   {
      if (Mutex::TryOBD2())
      {
         qDebug() << "ERROR CODES: getting error codes..."; 

         /* get error codes here */

         Mutex::UnlockOBD2();

         /* turn the button back on */
         getButton->setEnabled(true);
         waiting = false;
      }
      
      else
      {
         if (notifyFlag)
         {
             qDebug() << "ERROR CODES: waiting...";

             /* turn off the button while waiting */
             getButton->setEnabled(false);

             notifyFlag = false;
         }

         /* unblock the executive while waiting */
         qApp->processEvents();
      }
   } 
}


void ErrorCodes::ClearErrorCodes()
{
   std::cout<<"Clear Codes"<<std::endl;
}
