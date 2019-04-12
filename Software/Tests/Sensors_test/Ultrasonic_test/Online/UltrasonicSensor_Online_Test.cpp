/**
 * @file UltrasonicSensor_Online_Test.cpp
 * @author Jamie Brown/Joe Walker
 * @brief Contains online unit tests for the ultrasonic_sensor class
 * @version 0.2
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include "ultrasonic_sensor.h"
#include "types.h"
#include "config.h"


using namespace std;

/**
 * @brief Online unit tests for the ultrasonic_sensor class.
 * 
 */

class UltrasonicSensorOnlineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for ultrasonic_sensor */
    void init_Test();
    void GetDistance_Test();
    
    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private:
    ultrasonic_sensor *m_sensor;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief This method is called before the first test case
 * 
 */
void UltrasonicSensorOnlineTest::initTestCase()
{
    qDebug() << "initTestCase";
#ifdef RPI
    //setup wiringpi
    wiringPiSetup();
#endif
}

/**
 * @brief This method is called after the last test case
 * 
 */
void UltrasonicSensorOnlineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief This method is called before each test case, creates a new ultrasonic_sensor
 * 
 */
void UltrasonicSensorOnlineTest::init()
{
    qDebug() << "init";
    m_sensor = new ultrasonic_sensor();
}

/**
 * @brief This method is called after each test case, it deletes the ultrasonic_sensor
 * 
 */
void UltrasonicSensorOnlineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_sensor;
}


/*----------------------------------------*/
/* UNIT TESTS FOR ULTRASONIC_SENSOR CLASS */
/*----------------------------------------*/


/**
 * @brief Tests the init function
 * 
 */
void UltrasonicSensorOnlineTest::init_Test()
{
    qDebug() << "Testing the init function";
    QVERIFY2(m_sensor->init(14, 12)==true, "Check RPI define in config file");
}

/**
 * @brief 
 * 
 */
void UltrasonicSensorOnlineTest::GetDistance_Test()
{
    qDebug() << "Testing the getDistance function";
    double testVal = -1;
    QVERIFY2(m_sensor->GetDistance(&testVal)==true, "No echo pulse detected");
    QVERIFY2(testVal >= 0, "Negative distance value returned");
}

/* run tests */
//QTEST_MAIN(UltrasonicSensorOnlineTest);
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    UltrasonicSensorOnlineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "UltrasonicSensor_Online_Test.moc"