#include "GUIThread.h"
#include <QtCore>
#include <stdio.h>
#include "StateManager.h"



GUIThread::GUIThread()
{
    
}


void GUIThread::run()
{
    printf("Starting GUI thread...\n");
    //StateManager stateMachine;
    //stateMachine.show();
    exec();
}