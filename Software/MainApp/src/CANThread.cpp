/**
 * @file StateManager.cpp
 * @author Jamie Brown
 * @brief Implemetation of CANThread.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "config.h"
#include "CANThread.h"
#include <QtCore>
#include <iostream>
#include <string>

using namespace std;

CANThread::CANThread()
{

}

CANThread::~CANThread()
{
    
    delete this;
}

void CANThread::run()
{
    qDebug() << "CAN THREAD: starting...";
    
    /* kick off the thread */
    exec();
}




