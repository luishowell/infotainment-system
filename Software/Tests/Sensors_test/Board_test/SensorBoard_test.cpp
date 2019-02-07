#include <QtTest/QtTest>
#include <iostream>
//#include "sensor_board.h"
//#include "types.h"

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
    //m_board = new sensor_board();
}

/* called after each test case */
void SensorBoardTest::cleanup()
{
    //delete m_board;
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

QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    int ret;

    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);
    
    SensorBoardTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    ret = QTest::qExec(&tc, argc, argv);

    /* output number of failed tests */
    cout << ret << endl;
    return 0;

}

#include "SensorBoard_test.moc"