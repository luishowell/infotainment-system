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
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "SensorThread.h"

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
//#ifdef RPI
    SensorThread sensorsThr;
//#endif
    
    cout << "INFOTAINYOU: created obd object" << endl;
    CANWorker canW(myObd);
    cout << "INFOTAINYOU: created CAN worker object" << endl;
    
    qRegisterMetaType<QVector<QString>>("<QVector<QString>>");
    QObject::connect(&stateMachine, SIGNAL(LogRequestTx(QVector<QString>, bool)), &canW, SLOT(LogRequestRx(QVector<QString>, bool)));

    canW.moveToThread(&canT);	
    cout << "INFOTAINYOU: moved worker to thread" << endl;
    QObject::connect(&canT, SIGNAL(started()), &canW, SLOT(GetDiagData()));
    QObject::connect(&canW, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &canW, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

//#ifdef RPI
    QObject::connect(&sensorsThr, SIGNAL(SensorPublishDiagTx(sensorDist_t*)), &stateMachine, SLOT(SensorPublishDiagRx(sensorDist_t*)));
//#endif

    cout << "INFOTAINYOU: made connections" << endl;

    /*
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    stateMachine.setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    */

    /* start threads */
    canT.start();
//#ifdef RPI
    sensorsThr.start();
//#endif

#ifdef RPI
    stateMachine.showFullScreen();
#else
    stateMachine.show();
#endif

    /* kick off GUI event loop */
    return app.exec();
}

//Q_DECLARE_METATYPE(QVector<QString>)