/**
 * @file Mutex.cpp
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-03-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QMutex>
#include "Mutex.h"

namespace Mutex
{
    QMutex OBD2Mutex;

    void LockOBD2()
    {
        OBD2Mutex.lock();
    }

    bool TryOBD2()
    {
        return OBD2Mutex.tryLock();
    }

    void UnlockOBD2()
    {
        OBD2Mutex.unlock();
    }
}
