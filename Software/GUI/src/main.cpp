#include <stdio.h>
#include <QApplication>
#include <QtCore>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "StateManager.h"
#include "config.h"
#include "CANThread.h"
#include "GUIThread.h"

int main(int argc, char** argv)
{
    printf("Starting heads-up display...\n");
    QApplication app (argc, argv);

    QQuickView view;
    view.setSource(QUrl::fromLocalFile("../../../../src/Speedometer.qml"));
    view.show();
    QObject *object = view.rootObject();
    object->setProperty("value", 25);
    
    /* GUI stuff in state machine class*/
    StateManager stateMachine;
    stateMachine.show();

    /* create and start the CAN thread */
    CANThread can;
    QObject::connect(&can, SIGNAL(CANPublishDiagTx(diagMsg_t*)), &stateMachine, SLOT(CANPublishDiagRx(diagMsg_t*)));
    can.start();
  
    /* kick off GUI event loop */
    return app.exec();
}