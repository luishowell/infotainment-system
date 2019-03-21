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
#include "AccThread.h"
#include "AccWorker.h"
#include "acc_gauge.h"

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
    MMA8652FCR1* guiAccel;

    

    /* create threads */
    CANThread canT;
    CANWorker canW(myObd);
    SensorThread sensorT;
    SensorWorker sensorW;
    AccThread accT;
    AccWorker accW;

    /* GUI stuff in state machine class*/
    StateManager stateMachine(0, myObd, accW.acc);
    
    
    /* move workers into appropriate threads */
    canW.moveToThread(&canT);
    accW.moveToThread(&accT);
    //sensorW.moveToThread(&sensorT);	


    qRegisterMetaType<QVector<QString>>("<QVector<QString>>");
    QObject::connect(&stateMachine, SIGNAL(LogRequestTx(QVector<QString>, bool)), &canW, SLOT(LogRequestRx(QVector<QString>, bool)));

    

    QObject::connect(&canT, SIGNAL(started()), &canW, SLOT(GetDiagData()));
    //QObject::connect(&sensorT, SIGNAL(started()), &sensorW, SLOT(Work()));
    QObject::connect(&accT, SIGNAL(started()), &accW, SLOT(Work()));

    /* connect CAN thread data to GUI */
    QObject::connect(&canW, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &canW, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

    /* connect acc thread data to GUI */
    QObject::connect(&accW, SIGNAL(SendData(accValues_t*)), &stateMachine, SLOT(AccDataRx(accValues_t*)));

    QObject::connect(&sensorW, SIGNAL(SensorPublishDiagTx(sensorDist_t*)), &stateMachine, SLOT(SensorPublishDiagRx(sensorDist_t*)));

    /* start threads */
    canT.start();
    sensorT.start();
    accT.start();

#ifdef RPI
    stateMachine.showFullScreen();
    QApplication::setOverrideCursor(Qt::BlankCursor); //removes cursor on touchscreen
#else
    stateMachine.show();
#endif

    /* kick off GUI event loop */
    return app.exec();
}

//Q_DECLARE_METATYPE(QVector<QString>)