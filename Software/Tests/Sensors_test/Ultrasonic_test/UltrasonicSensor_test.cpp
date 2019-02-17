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
#include "UltrasonicSensor_test.h"


using namespace std;

class UltrasonicSensorTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for ultrasonic_sensor */
    void UltrasonicSensor_Test();
    void init_Test();
    void GetDistance_Test();
    
    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private:
    //ultrasonic_sensor *m_sensor;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief This method is called before the first test case
 * 
 */
void UltrasonicSensorTest::initTestCase()
{

}

/**
 * @brief This method is called after the last test case
 * 
 */
void UltrasonicSensorTest::cleanupTestCase()
{

}

/**
 * @brief This method is called before each test case, creates a new ultrasonic_sensor
 * 
 */
void UltrasonicSensorTest::init()
{
    m_sensor = new ultrasonic_sensor();
}

/**
 * @brief This method is called after each test case, it deletes the ultrasonic_sensor
 * 
 */
void UltrasonicSensorTest::cleanup()
{
    delete m_sensor;
}


/*----------------------------------------*/
/* UNIT TESTS FOR ULTRASONIC_SENSOR CLASS */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void UltrasonicSensorTest::UltrasonicSensor_Test()
{

}

/**
 * @brief 
 * 
 */
void UltrasonicSensorTest::init_Test()
{

}

/**
 * @brief 
 * 
 */
void UltrasonicSensorTest::GetDistance_Test()
{

}

/* run tests */
//QTEST_MAIN(UltrasonicSensorTest);
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    UltrasonicSensorTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "UltrasonicSensor_test.moc"