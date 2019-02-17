/**
 * @file GUIThread.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "GUIThread.h"
#include <QtCore>
#include <iostream>
//#include <stdio.h>
#include "StateManager.h"

using namespace std;

/**
 * @brief Construct a new GUIThread::GUIThread object
 * 
 */
GUIThread::GUIThread()
{
    
}

/**
 * @brief 
 * 
 */
void GUIThread::run()
{
    cout<<"Starting GUI thread..."<<endl;
    //StateManager stateMachine;
    //stateMachine.show();
    exec();
}