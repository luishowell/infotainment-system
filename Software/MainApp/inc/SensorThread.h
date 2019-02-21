#ifndef SENSORTHREAD_H
#define SENSORTHREAD_H

#include "config.h"

#include <QThread>
#include "types.h"

#ifndef GUI_TEST
#include "sensor_board.h"
#endif

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
	void DummyData();

#ifndef GUI_TEST
    sensor_board* m_mux;
    /*
    UltrasonicSensor *m_frontLeft;
    UltrasonicSensor *m_frontRight;
    UltrasonicSensor *m_rearLeft;
    UltrasonicSensor *m_rearRight;
    */

#endif
};


#endif //SENSORTHREAD_H