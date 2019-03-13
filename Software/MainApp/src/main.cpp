/**
 * @file main.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "config.h"
#include "StateManager.h"
#include "CANThread.h"
#include "CANWorker.h"
#include "GUIThread.h"
#include "SensorWorker.h"
#include "SensorThread.h"

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
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

using namespace std;

//#define RPI 1

int main(int argc, char** argv)
{
    cout << "/***************LET ME INFOTAIN YOU!/***************" << endl;
    QApplication app (argc, argv);

    qApp->setStyle(QStyleFactory::create("macintosh"));

    obd2* myObd = new obd2("/dev/rfcomm0");

    /* GUI stuff in state machine class*/
    StateManager stateMachine(0, myObd);
    cout << "INFOTAINYOU: created state manager" << endl;

    /* create threads */
    CANThread canT;
    SensorThread sensorT;
    CANWorker canW(myObd);
    SensorWorker sensorW;
    /* move workers into appropriate threads */
    canW.moveToThread(&canT);
    //sensorW.moveToThread(&sensorT);	


    qRegisterMetaType<QVector<QString>>("<QVector<QString>>");
    QObject::connect(&stateMachine, SIGNAL(LogRequestTx(QVector<QString>, bool)), &canW, SLOT(LogRequestRx(QVector<QString>, bool)));

    

    QObject::connect(&canT, SIGNAL(started()), &canW, SLOT(GetDiagData()));
    //QObject::connect(&sensorT, SIGNAL(started()), &sensorW, SLOT(Work()));

    QObject::connect(&canW, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &canW, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

    QObject::connect(&sensorW, SIGNAL(SensorPublishDiagTx(sensorDist_t*)), &stateMachine, SLOT(SensorPublishDiagRx(sensorDist_t*)));

    /* start threads */
    canT.start();
    sensorT.start();

#ifdef RPI
    stateMachine.showFullScreen();
#else
    stateMachine.show();
#endif

    /* kick off GUI event loop */
    return app.exec();
}

//Q_DECLARE_METATYPE(QVector<QString>)