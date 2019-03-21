/**
 * @file AccThread.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "AccThread.h"

#include <QtCore>

AccThread::AccThread()
{

}

AccThread::~AccThread()
{

}

void AccThread::run()
{
    qDebug() << "ACC THREAD: starting accelerometer thread...";
    exec();
}