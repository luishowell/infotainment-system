#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include "config.h"

#include <QThread>

class SensorThread : public QThread
{
    Q_OBJECT

public:
    explicit SensorThread();

private:
    void run();
};


#endif //SENSORTHREAD_H