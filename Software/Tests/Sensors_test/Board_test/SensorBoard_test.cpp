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

class SensorBoardTest: public QObject
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
    //sensor_board *m_board;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void SensorBoardTest::initTestCase()
{
    //cout << "STARTING UNIT TESTS FOR SENSOR BOARD" << endl;
}

/**
 * @brief 
 * 
 */
void SensorBoardTest::cleanupTestCase()
{
    //cout << "FINISHED UNIT TESTS FOR SENSOR BOARD" << endl;
}

/**
 * @brief 
 * 
 */
void SensorBoardTest::init()
{
    m_board = new sensor_board();
}

/**
 * @brief 
 * 
 */
void SensorBoardTest::cleanup()
{
    delete m_board;
}

/*----------------------------------------*/
/*    UNIT TESTS FOR SENSOR_BOARD CLASS   */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void SensorBoardTest::SensorBoard_Test()
{
    //QCOMPARE(3, 7);
}

/**
 * @brief 
 * 
 */
void SensorBoardTest::init_Test()
{

}

/**
 * @brief 
 * 
 */
void SensorBoardTest::GetDistance_Test()
{
    
}

/* run tests */
//QTEST_MAIN(SensorBoardTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    SensorBoardTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "SensorBoard_test.moc"