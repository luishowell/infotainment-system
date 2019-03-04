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
//#include "SensorThread.h"

using namespace std;

int main(int argc, char** argv)
{
    cout<<"Starting heads-up display..."<<endl;
    QApplication app (argc, argv);

    qApp->setStyle(QStyleFactory::create("macintosh"));
    
    /* GUI stuff in state machine class*/
    StateManager stateMachine;
    cout << "created state manager" << endl;

    /* create threads */
    CANThread canT;
    //SensorThread sensorsThr;
#ifndef GUI_TEST
    obd2* myObd = new obd2("/dev/rfcomm0");
    cout << "created obd object" << endl;
    CANWorker canW(myObd);
    cout << "created CAN worker object" << endl;
    stateMachine.m_diags->obd = myObd;
    cout << "set obd to diag" << endl;
    stateMachine.m_diags->CreateLayout();
#else
    CANWorker canW;
#endif
    
    qRegisterMetaType<QVector<QString>>("<QVector<QString>>");
    QObject::connect(&stateMachine, SIGNAL(LogRequestTx(QVector<QString>, bool)), &canW, SLOT(LogRequestRx(QVector<QString>, bool)));

    canW.moveToThread(&canT);	
    cout << "moved worker to thread" << endl;
    QObject::connect(&canT, SIGNAL(started()), &canW, SLOT(GetDiagData()));
    QObject::connect(&canW, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    QObject::connect(&stateMachine, SIGNAL(NewChannelRequest(diagParams_t, obd2Channel_t)), &canW, SLOT(OnNewChannelRequest(diagParams_t, obd2Channel_t)));

    //QObject::connect(&sensorsThr, SIGNAL(SensorPublishDiagTx(sensorDist_t*)), &stateMachine, SLOT(SensorPublishDiagRx(sensorDist_t*)));
    cout << "made connections" << endl;

    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect();
    stateMachine.setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(350);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
    

    /* start threads */
    canT.start();
    //sensorsThr.start();
    //stateMachine.showFullScreen();
    stateMachine.show();

    /* kick off GUI event loop */
    return app.exec();
}

//Q_DECLARE_METATYPE(QVector<QString>)