/**
 * @file StateManager.cpp
 * @author Jamie Brown
 * @brief Contains implementation of the StateManager class
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "config.h"
#include "StateManager.h"

#include <QApplication>
#include <iostream>

using namespace std;

/**
 * @brief Construct a new State Manager:: State Manager object
 * 
 * @param parent The parent object of the state manager
 */
StateManager::StateManager(QWidget *parent, obd2* myObd, MMA8652FCR1* acc) : QWidget(parent)
{
    cout << "State manager started" << endl;

    m_obd = myObd;

    setFixedSize(widgetSize);

    /* create GUI views */
    
    m_mainMenu = new MainMenu(this);
    //qDebug() << "hi";
    m_diags = new Diagnostics(this, m_obd, acc);
    m_errorCodes = new ErrorCodes(this, m_obd);
    m_parking = new Parking(this);
    m_media = new Media(this);

     /* connect state request signals to state-machine */
    connect(m_mainMenu, SIGNAL (DisplayChange(state_t, QWidget*)), this, SLOT (ChangeRequested(state_t, QWidget*)));
    connect(m_diags, SIGNAL (DisplayChange(state_t, QWidget*)), this, SLOT (ChangeRequested(state_t, QWidget*)));
    connect(m_errorCodes, SIGNAL (DisplayChange(state_t, QWidget*)), this, SLOT (ChangeRequested(state_t, QWidget*)));
    connect(m_parking, SIGNAL (DisplayChange(state_t, QWidget*)), this, SLOT (ChangeRequested(state_t, QWidget*)));
    connect(m_media, SIGNAL (DisplayChange(state_t, QWidget*)), this, SLOT (ChangeRequested(state_t, QWidget*)));

    /* connect hardware data channels from other threads to specific GUI windows */
    connect(this, SIGNAL(DiagDataTx(diagMsg_t*)), m_diags, SLOT(DiagDataRx(diagMsg_t*)));
    connect(this, SIGNAL(AccDataTx(accValues_t*)), m_diags, SLOT(AccDataRx(accValues_t*)));

    connect(m_diags, SIGNAL(StartLogging(QVector<QString>, bool)), this, SLOT(LogRequestRx(QVector<QString>, bool)));

    connect(this, SIGNAL(SensorTx(sensorDist_t*)), m_parking, SLOT (SensorRx(sensorDist_t*)));

    /* show the home menu on startup */
    m_mainMenu->show();
    m_diags->hide();
    m_errorCodes->hide();
    m_parking->hide();
    m_media->hide();

}

/**
 * @brief Receiving callback of diagnostics data from the CAN thread
 * 
 * @param msg 
 */
void StateManager::CANPublishDiagRx(diagMsg_t* msg)
{
    /* forward to diagnostics window */
    emit DiagDataTx(msg);
}

void StateManager::AccDataRx(accValues_t* msg)
{
    qDebug() << "STATE MANAGER: received acc data";

    /* forward to diagnostics window */
    emit AccDataTx(msg);
}

/**
 * @brief State machine that determines the currently displayed view/menu
 * 
 * @param req_state The requested view to be shown
 * @param currentView A pointer to the currently displayed view
 */
void StateManager::ChangeRequested(state_t req_state, QWidget* currentView)
{
    switch(req_state)
    {
        case MAIN_MENU : { 
            cout << "Main Menu" << endl;
            if (currentView != m_mainMenu)
            {
                currentView->hide();
                m_mainMenu->show();
            }           
            break;
        }
        case DIAGNOSTICS : {
            cout <<"Diagnostics" << endl; 
            if (currentView != m_diags)
            {
               currentView->hide();
               m_diags->show(); 
            }
            break;    
        }
        case ERROR_CODES : { 
            cout <<"Error Codes"<<endl; 

            if (currentView != m_errorCodes)
            {
               currentView->hide();
               m_errorCodes->show(); 
            }
            break;
        }
        case MEDIA : {
            cout<<"Media"<<endl; 
            if (currentView != m_media)
            {
               currentView->hide();
               m_media->show(); 
            }
            break;
        }
        case PARKING : {
            cout<<"Parking"<<endl;
            if (currentView != m_parking)
            {
               currentView->hide();
               m_parking->show(); 
            }
            break;
        }
        default : { 
            cout << "Not a valid option" << endl;
            break;
        }         
    }
}

/**
 * @brief Forwards new data channel request information from the GUI to the CAN thread
 * 
 * @param dataRequested The data parameter that is requested (eg. speed, rpm etc)
 * @param channel The requested channel number (left or right)
 */
void StateManager::OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel)
{
    //cout<<"CHANNEL REQUESTED"<<endl;
    /* forward to the OBD2 thread */
    emit NewChannelRequest(dataRequested, channel);
}

/**
 * @brief 
 * 
 * @param logParams 
 */
void StateManager::LogRequestRx(QVector<QString> logParams, bool start)
{
    qDebug() << "STATE MANAGER: logging";
    emit LogRequestTx(logParams, start);
}


void StateManager::SensorPublishDiagRx(sensorDist_t* sensorData)
{
  //cout << "SENSOR DATA: " << sensorData->rearLeft << endl;
  emit SensorTx(sensorData);
}