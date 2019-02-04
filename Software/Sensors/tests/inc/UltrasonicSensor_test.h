#include <QtTest/QtTest>
#include "ultrasonic_sensors.h"

class UltrasonicSensorTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for ultrasonic_sensor */
    void UltrasonicSensor_Test();
    void init_Test();
    void GetDistance_Test();

private:
    ultrasonic_sensor *m_sensor;
};
