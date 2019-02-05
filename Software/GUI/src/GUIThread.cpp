#include "GUIThread.h"
#include <QtCore>
#include <iostream>
//#include <stdio.h>
#include "StateManager.h"

using namespace std;

GUIThread::GUIThread()
{
    
}


void GUIThread::run()
{
    cout<<"Starting GUI thread..."<<endl;
    //StateManager stateMachine;
    //stateMachine.show();
    exec();
}