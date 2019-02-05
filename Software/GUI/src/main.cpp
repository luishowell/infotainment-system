//#include <stdio.h>
#include <iostream>
#include <QApplication>
#include <QtCore>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QStyleFactory>

#include "StateManager.h"
#include "config.h"
#include "CANThread.h"
#include "GUIThread.h"

using namespace std;

int main(int argc, char** argv)
{
    cout<<"Starting heads-up display..."<<endl;
    QApplication app (argc, argv);

    qApp->setStyle(QStyleFactory::create("macintosh"));
    
    /* GUI stuff in state machine class*/
    StateManager stateMachine;
    stateMachine.show();

    /* create and start the CAN thread */
    CANThread can;
    QObject::connect(&can, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &can, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

    can.start();
  
    /* kick off GUI event loop */
    return app.exec();
}