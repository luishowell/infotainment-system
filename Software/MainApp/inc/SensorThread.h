#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include <QThread>
#include "Timer.h"
#include "types.h"
#include "sensor_board.h"


class SensorThread : public QThread
{
    Q_OBJECT

public:
    explicit SensorThread();
    
private slots:
    void PublishSensorData();

signals:
    void SensorPublishDiagTx(sensorDist_t* msg);

private:
    sensorDist_t* m_msg;
    void run();
	sensor_board* m_mux;
	void DummyData();
    /*
    UltrasonicSensor *m_frontLeft;
    UltrasonicSensor *m_frontRight;
    UltrasonicSensor *m_rearLeft;
    UltrasonicSensor *m_rearRight;
    */
};


#endif //SENSORTHREAD_H