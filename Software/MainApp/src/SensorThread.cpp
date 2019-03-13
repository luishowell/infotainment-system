/**
 * @file SensorThread.cpp
 * @author Jamie Brown
 * @brief 
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

/**
 * @brief Construct a new Sensor Thread:: Sensor Thread object
 * 
 */
SensorThread::SensorThread()
{  
	
}

/**
 * @brief 
 * 
 */
void SensorThread::run()
{
    cout<<"SENSOR THREAD: starting sensor thread..."<<endl;

    /* kick off the thread */
    exec();

    //JB: was using the following code to test the mutexes ( comment out exec(); )
    /*
    while (true)
    {
        Mutex::LockOBD2();
        sleep(5);
        Mutex::UnlockOBD2();
        qApp->processEvents();
    }
    */
}
                           