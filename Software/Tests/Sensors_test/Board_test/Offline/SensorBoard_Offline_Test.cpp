/**
 * @file SensorBoard_test.cpp
 * @author Jamie Brown/Joe Walker
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include "sensor_board.h"
#include "types.h"

using namespace std;

class SensorBoardOfflineTest: public QObject
{
    Q_OBJECT

private slots:
    /* unit tests for sensor_board */
    void SensorBoard_Test();
    void init_Test();
    void GetDistance_Test();

    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private:
    sensor_board *m_board;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void SensorBoardOfflineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief 
 * 
 */
void SensorBoardOfflineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief 
 * 
 */
void SensorBoardOfflineTest::init()
{
    qDebug() << "init";
    m_board = new sensor_board();
}

/**
 * @brief 
 * 
 */
void SensorBoardOfflineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_board;
}

/*----------------------------------------*/
/*    UNIT TESTS FOR SENSOR_BOARD CLASS   */
/*----------------------------------------*/

/**
 * @brief Test the constructor
 * 
 */
void SensorBoardOfflineTest::SensorBoard_Test()
{
    
}

/**
 * @brief Test the init function
 * 
 */
void SensorBoardOfflineTest::init_Test()
{
    qDebug() << "Testing the init function";

    sensorPins_t testPins;
    QVERIFY2(m_board->init(testPins)==false, "Check RPI define in config file");
}

/**
 * @brief Test the getDistance function
 * 
 */
void SensorBoardOfflineTest::GetDistance_Test()
{
    qDebug() << "Testing the getDistance function";

    double testDistance;
    QVERIFY2(m_board->GetDistance(1, &testDistance)==false, "Check RPI define in config file");
    QVERIFY2(m_board->GetDistance(-1, &testDistance)==false, "Check RPI define in config file");
}

/* run tests */
//QTEST_MAIN(SensorBoardOfflineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    SensorBoardOfflineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "SensorBoard_Offline_Test.moc"