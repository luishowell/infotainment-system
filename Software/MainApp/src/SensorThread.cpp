/**
 * @file SensorThread.cpp
 * @author Jamie Brown
 * @brief Implementation of SensorThread.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "SensorThread.h"
#include "Mutex.h"

#include <QtCore>
#include <iostream>
#include <unistd.h>

using namespace std;


SensorThread::SensorThread()
{  
	
}

void SensorThread::run()
{
    cout<<"SENSOR THREAD: starting sensor thread..."<<endl;

    /* kick off the thread */
    exec();

}
                           