/**
 * @file StateManager.cpp
 * @author Jamie Brown
 * @brief 
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

/**
 * @brief Construct a new CANThread::CANThread object
 * 
 */
CANThread::CANThread()
{

}

/**
 * @brief Destroy the CANThread::CANThread object
 * 
 */
CANThread::~CANThread()
{
    
    delete this;
}

/**
 * @brief 
 * 
 */
void CANThread::run()
{
    qDebug() << "CAN THREAD: starting...";
    
    /* kick off the thread */
    exec();
}

/* JB: moved to worker class for now */
/**
 * @brief 
 * 
 */
void CANThread::PublishDiagData()
{
  qDebug() << "CAN THREAD: Publishing diag...";
  
}



