#include <iostream>
#include "ultrasonic_sensor.h"
#include "types.h"

using namespace std;

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void UltrasonicSensorTest::initTestCase()
{
    cout << "STARTING UNIT TESTS FOR ULTRASONIC SENSOR" << endl;
}

void UltrasonicSensorTest::cleanupTestCase()
{
    cout << "FINISHED UNIT TESTS FOR ULTRASONIC SENSOR" << endl;
}

/* called before each test case */
void UltrasonicSensorTest::init()
{
    m_sensor = new ultransonic_sensor();
}

/* called after each test case */
void UltrasonicSensorTest::cleanup()
{
    delete m_sensor;
}

void UltrasonicSensorTest::init()
{

}

void UltrasonicSensorTest::cleanupTestCase()
{

}

/*----------------------------------------*/
/* UNIT TESTS FOR ULTRASONIC_SENSOR CLASS */
/*----------------------------------------*/

void UltrasonicSensorTest::UltrasonicSensor_Test()
{

}

void UltrasonicSensorTest::init_Test()
{

}

void UltrasonicSensorTest::GetDistance_Test()
{

}

/* run tests */
QTEST_MAIN(UltrasonicSensorTest)
#include "UltrasonicSensor_test.moc"