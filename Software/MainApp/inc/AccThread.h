/**
 * @file AccThread.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ACCTHREAD_H
#define ACCTHREAD_H

/** @brief Thread that obtains data from the OBD2 bus on a periodic basis
 * 
 * @author Jamie Brown
 * @date February 2019
 * */

#include "config.h"
#include "types.h"

#include <QThread>
#include <string>

class AccThread : public QThread
{
    Q_OBJECT

public:
    explicit AccThread();
    ~AccThread();

private:
    void run();
};


#endif //ACCTHREAD_H