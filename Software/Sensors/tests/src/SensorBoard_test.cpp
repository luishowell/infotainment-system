#include <iostream>
#include "sensor_board.h"
#include "types.h"

using namespace std;

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void SensorBoardTest::initTestCase()
{
    cout << "STARTING UNIT TESTS FOR SENSOR BOARD" << endl;
}

void SensorBoardTest::cleanupTestCase()
{
    cout << "FINISHED UNIT TESTS FOR SENSOR BOARD" << endl;
}

/* called before each test case */
void SensorBoardTest::init()
{
    m_board = new sensor_board();
}

/* called after each test case */
void SensorBoardTest::cleanup()
{
    delete m_board;
}

/*----------------------------------------*/
/*    UNIT TESTS FOR SENSOR_BOARD CLASS   */
/*----------------------------------------*/

void SensorBoardTest::SensorBoard_Test()
{

}

void SensorBoardTest::init_Test()
{

}

void SensorBoardTest::GetDistance_Test()
{
    
}

QTEST_MAIN(SensorBoardTest)
#include "SensorBoard_test.moc"