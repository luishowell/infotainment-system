#include <stdio.h>
#include <QApplication>
#include <QtCore>
#include "StateManager.h"
#include "config.h"
#include "CANThread.h"
#include "GUIThread.h"

int main(int argc, char** argv)
{
    printf("Starting heads-up display...\n");
    QApplication app (argc, argv);

    /* GUI stuff in state machine class*/
    StateManager stateMachine;
    stateMachine.show();

    /* create and start the CAN thread */
    CANThread can;
    QObject::connect(&can, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    can.start();
  
    /* kick off GUI event loop */
    return app.exec();

    /*
    for(;;)
    {

    }
   
    return 0; 
    */
}