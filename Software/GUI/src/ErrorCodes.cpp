#include "ErrorCodes.h" 
#include "config.h"
#include "Mutex.h"

#include <QtCore>
#include <QApplication>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>


ErrorCodes::ErrorCodes(QWidget *parent, obd2* myObd) : QWidget(parent) 
{
   obd = myObd;
      
   setFixedSize(widgetSize);

   CreateLayout();    

   connect(m_homeButton, SIGNAL (clicked()), this, SLOT (StateChangeMainMenu()));    
   connect(getButton, SIGNAL (clicked()), this, SLOT (GetErrorCodes()));
   connect(clearButton, SIGNAL (clicked()), this, SLOT (ClearErrorCodes()));
}

void ErrorCodes::StateChangeMainMenu()
{
   emit DisplayChange(MAIN_MENU, this);
}

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

   errorTable = new QTableWidget(0, 2, this);
   errorTable->horizontalHeader()->setStretchLastSection(true);
   errorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);   //prevent table editing
   errorTable->setHorizontalHeaderLabels(QStringList() << "Error Code" << "Description");

   getButton = new QPushButton("Get Error Codes");
   clearButton = new QPushButton("Clear Error Codes");   
   getButton->setMinimumHeight(80);
   clearButton->setMinimumHeight(80);

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
   vector<string> dtc_codes;

   //qDebug() << "ERROR CODES: clicked";
   while (waiting)
   {
      if (Mutex::TryOBD2())
      {
         qDebug() << "ERROR CODES: getting error codes..."; 

         /* get error codes here */
         dtc_codes = obd->read_dtc();
         errorTable->setRowCount(dtc_codes.size());

         if (dtc_codes.size()>0)
         {
            for (int i=0; i<dtc_codes.size(); i++)
            {
               errorTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dtc_codes[i])));
               std::string desc = obd->dtc_desc(dtc_codes[i]);
               errorTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(desc)));
            }
         }
         else
         {
            QMessageBox msgBox;
            msgBox.setText("No current trouble codes!");
            msgBox.exec();
         }

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
   bool waiting = true;
   bool notifyFlag = true; 

   //qDebug() << "ERROR CODES: clicked";
   while (waiting)
   {
      if (Mutex::TryOBD2())
      {
         qDebug() << "ERROR CODES: getting error codes..."; 

         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "Clear DTC codes", "Are you sure you want to clear DTC codes?\nThink carefully...", 
         QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) 
         {
            std::cout<<"Clearing diagnostic trouble codes..."<<std::endl;
            string rec = obd->send_cmd("04", false);
            std::cout<<"Clear DTC rec: "<<rec<<std::endl;
            
            QMessageBox msgBox;
                  
            if (rec.find("44")!=string::npos)
            {
               errorTable->setRowCount(0);
               msgBox.setText("DTC Reset Success!");
            }
            else
            {
               std::string failed_msg = R"(DTC Reset Failed: Some vehicles may
               require a special condition to occur (eg. the ignition on
               but the engine must not be running) before they will
               respond to a clear command.)";
               msgBox.setText(QString::fromStdString(failed_msg));
            }
            msgBox.exec();      
         } 
         else
         {
            std::cout<<"Clear Codes Cancelled"<<std::endl;
         }

         Mutex::UnlockOBD2();

         /* turn the button back on */
         clearButton->setEnabled(true);
         waiting = false;
      }
      
      else
      {
         if (notifyFlag)
         {
             qDebug() << "ERROR CODES: waiting...";

             /* turn off the button while waiting */
             clearButton->setEnabled(false);

             notifyFlag = false;
         }

         /* unblock the executive while waiting */
         qApp->processEvents();
      }
   } 
}
