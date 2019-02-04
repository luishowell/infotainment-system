#include <iostream>
#include "multiplexor.h"
#include "types.h"

using namespace std;

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void MultiplexorTest::initTestCase()
{
    cout << "STARTING UNIT TESTS FOR MULTIPLEXOR" << endl;
}

void MultiplexorTest::cleanupTestCase()
{
    cout << "FINISHED UNIT TESTS FOR MULTIPLEXOR" << endl;
}

/* called before each test case */
void MultiplexorTest::init()
{
    m_mux = new multiplexor();
}

/* called after each test case */
void MultiplexorTest::cleanup()
{
    delete m_mux;
}

/*----------------------------------------*/
/*     UNIT TESTS FOR MULTIPLEXOR CLASS   */
/*----------------------------------------*/

/* constructor test */
void MultiplexorTest::Multiplexor_Test()
{

}

void MultiplexorTest::Init_Test()
{

}

void MultiplexorTest::SetMux_Test()
{

}

/* run tests */
QTEST_MAIN(UltrasonicSensorTest)
#include "UltrasonicSensor_test.moc"