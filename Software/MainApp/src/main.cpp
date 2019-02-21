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

#include "config.h"
#include "StateManager.h"
#include "config.h"
#include "CANThread.h"
#include "CANWorker.h"
#include "GUIThread.h"
//#include "SensorThread.h"

using namespace std;

int main(int argc, char** argv)
{
    cout<<"Starting heads-up display..."<<endl;
    QApplication app (argc, argv);

    qApp->setStyle(QStyleFactory::create("macintosh"));
    
    /* GUI stuff in state machine class*/
    StateManager stateMachine;
    

    /* create threads */
    CANThread canT;
#ifndef GUI_TEST
    obd2* myObd = new obd2("/dev/rfcomm0");
    CANWorker canW(myObd);
    stateMachine.m_diag->obd = myObd;
#else
    CANWorker canW;
#endif
    canW.moveToThread(&canT);	
    QObject::connect(&canT, SIGNAL(started()), &canW, SLOT(GetDiagData()));
    QObject::connect(&canW, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &canW, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

    /* create and start the sensor thread */
    //SensorThread sensorsThr;

    /* start threads */
    canT.start();
    //sensorsThr.start();
    stateMachine.show();

    /* kick off GUI event loop */
    return app.exec();
}