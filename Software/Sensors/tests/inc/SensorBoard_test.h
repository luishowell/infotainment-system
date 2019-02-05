#include <QtTest/QtTest>
#include "sensor_board.h"

class SensorBoardTest: public QObject
{
    Q_OBJECT

private slots:
    /* unit tests for sensor_board */
    void sensor_board_Test();
    void init_Test();
    void GetDistance_Test();

private:
    sensor_board *m_board;
};
