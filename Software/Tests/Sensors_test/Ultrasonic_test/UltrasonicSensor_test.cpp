#include <QtTest/QtTest>
#include <iostream>
//#include "ultrasonic_sensor.h"
//#include "types.h"
//#include "UltrasonicSensor_test.h"


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

void UltrasonicSensorTest::initTestCase()
{
    //cout << "STARTING UNIT TESTS FOR ULTRASONIC SENSOR" << endl;
}

void UltrasonicSensorTest::cleanupTestCase()
{
    //cout << "FINISHED UNIT TESTS FOR ULTRASONIC SENSOR" << endl;
}

/* called before each test case */
void UltrasonicSensorTest::init()
{
    //m_sensor = new ultransonic_sensor();
}

/* called after each test case */
void UltrasonicSensorTest::cleanup()
{
    //delete m_sensor;
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