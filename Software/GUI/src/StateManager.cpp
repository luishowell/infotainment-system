#include <QApplication>
#include <stdio.h>
#include "StateManager.h"
#include "config.h"

StateManager::StateManager(QWidget *parent) : QWidget(parent)
{
    printf("State manager started\n");

    setFixedSize(widgetSize);

    /* create GUI views */
    m_mainMenu = new MainMenu(this);
    m_diags = new Diagnostics(this);
    m_errorCodes = new ErrorCodes(this);
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

    /* show the home menu on startup */
    m_mainMenu->show();
    m_diags->hide();
    m_errorCodes->hide();
    m_parking->hide();
    m_media->hide();

}

/* @brief: Receiving callback of diagnostics data from the CAN thread */
void StateManager::CANPublishDiagRx(diagMsg_t* msg)
{
    /* forward to diagnostics window */
    emit DiagDataTx(msg);
}

/* @brief: Current GUI view state-machine */
void StateManager::ChangeRequested(state_t req_state, QWidget* currentView)
{
    switch(req_state)
    {
        case MAIN_MENU : { 
            printf("Main Menu\n");
            if (currentView != m_mainMenu)
            {
                currentView->hide();
                m_mainMenu->show();
            }           
            break;
        }
        case DIAGNOSTICS : {
            printf("Diagnostics\n"); 
            if (currentView != m_diags)
            {
               currentView->hide();
               m_diags->show(); 
            }
            break;    
        }
        case ERROR_CODES : { 
            printf("Error Codes\n"); 

            if (currentView != m_errorCodes)
            {
               currentView->hide();
               m_errorCodes->show(); 
            }
            break;
        }
        case MEDIA : {
            printf("Media\n"); 
            if (currentView != m_media)
            {
               currentView->hide();
               m_media->show(); 
            }
            break;
        }
        case PARKING : {
            printf("Parking\n");
            if (currentView != m_parking)
            {
               currentView->hide();
               m_parking->show(); 
            }
            break;
        }
        default : { 
            printf("Not a valid option\n");
            break;
        }         
    }
}
