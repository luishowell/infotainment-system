#ifndef SENSORWORKER_H
#define SENSORWORKER_H

#include "config.h"

#include "types.h"
#include "sensor_board.h"

#include <QObject>

class SensorWorker : public QObject
{
    Q_OBJECT

public:
    explicit SensorWorker();
    
private slots:
    void PublishSensorData();
    void Work();

signals:
    void SensorPublishDiagTx(sensorDist_t* msg);

private:
    sensorDist_t* m_msg;
    //void run();
	void DummyData();
    QTimer* m_timer;
    sensor_board* m_mux;
  
};


#endif //SENSORTHREAD_H