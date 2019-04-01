/**
 * @file UltrasonicSensor_test.cpp
 * @author Jamie Brown/Joe Walker
 * @brief Contains unit tests for the ultrasonic_sensor class
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include "ultrasonic_sensor.h"
#include "types.h"
//#include "UltrasonicSensor_test.h"


using namespace std;

class UltrasonicSensorOfflineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for ultrasonic_sensor */
    void UltrasonicSensor_Test();
    void init_Test();
    void GetDistance_Test();
    void setTimeout_Test();
    void calculateDistance_Test();
    
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
void UltrasonicSensorOfflineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief This method is called after the last test case
 * 
 */
void UltrasonicSensorOfflineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief This method is called before each test case, creates a new ultrasonic_sensor
 * 
 */
void UltrasonicSensorOfflineTest::init()
{
    qDebug() << "init";
    m_sensor = new ultrasonic_sensor();
}

/**
 * @brief This method is called after each test case, it deletes the ultrasonic_sensor
 * 
 */
void UltrasonicSensorOfflineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_sensor;
}


/*----------------------------------------*/
/* UNIT TESTS FOR ULTRASONIC_SENSOR CLASS */
/*----------------------------------------*/

/**
 * @brief This method tests the constructor
 * 
 */
void UltrasonicSensorOfflineTest::UltrasonicSensor_Test()
{
    qDebug() << "Checking the constructor";
    QVERIFY2(m_sensor->timeoutLen == 11765, "Default timeout length is incorrect");
}

/**
 * @brief Tests the init function when not on a RPI
 * 
 */
void UltrasonicSensorOfflineTest::init_Test()
{
    qDebug() << "Testing the init function";
    QVERIFY2(m_sensor->init(0, 1)==false, "Check RPI define in config file");
}

/**
 * @brief Tests the getDistance function when the RPI is not connected
 * 
 */
void UltrasonicSensorOfflineTest::GetDistance_Test()
{
    qDebug() << "Testing the getDistance function";
    double testVal;
    QVERIFY2(m_sensor->GetDistance(&testVal)==false, "Check RPI define in config file");
}

/**
 * @brief Tests the getDistance function when the RPI is not connected
 * 
 */
void UltrasonicSensorOfflineTest::setTimeout_Test()
{
    qDebug() << "Testing the setTimeout function";

    //check the invalid timeout values
    QVERIFY2(m_sensor->setTimeout(-1)==false, "Function misses invalid value");
    QVERIFY2(m_sensor->setTimeout(6)==false, "Function misses invalid value");

    //check it works correctly for a valid value
    QVERIFY2(m_sensor->setTimeout(1)==true, "Function misses valid value");
    QVERIFY2(m_sensor->timeoutLen == 5882, "Timeout length is incorrect");
}

/**
 * @brief Tests the calculateDistance function
 * 
 */
void UltrasonicSensorOfflineTest::calculateDistance_Test()
{
    qDebug() << "Testing the calculateDistance function";

    //test the calculate distance function
    QVERIFY2(m_sensor->calculateDistance(5882) == 0.99994, 
    "Distance calculated incorrectly");

    //test with an invalid timeout value
    QVERIFY2(m_sensor->calculateDistance(-1) == -999, 
    "Invalid pulse length not recognised");

}

/* run tests */
//QTEST_MAIN(UltrasonicSensorOfflineTest);
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    UltrasonicSensorOfflineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "UltrasonicSensor_Offline_Test.moc"