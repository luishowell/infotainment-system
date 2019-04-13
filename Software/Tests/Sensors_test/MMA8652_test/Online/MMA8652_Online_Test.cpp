/**
 * @file MMA8652_Online_Test.cpp
 * @author Joe Walker
 * @brief Online tests for the MMA8652 class
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include "MMA8652FCR1.h"
#include "types.h"
#include "config.h"

using namespace std;

/**
 * @brief Online unit tests for the MMA8652FCR1 class.
 * 
 */

class MMA8652OnlineTest: public QObject
{
    Q_OBJECT

private slots:
    /* unit tests for mma8652 */
    void MMA8652_Test();
    void init_Test();
    void getData_Test();
    void recordStatic_Test();

    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private:
    MMA8652FCR1 *m_acc;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void MMA8652OnlineTest::initTestCase()
{
    qDebug() << "initTestCase";
#ifdef RPI
    //setup wiringpi
    wiringPiSetup();
#endif
}

/**
 * @brief 
 * 
 */
void MMA8652OnlineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief 
 * 
 */
void MMA8652OnlineTest::init()
{
    qDebug() << "init";
    m_acc = new MMA8652FCR1();
}

/**
 * @brief 
 * 
 */
void MMA8652OnlineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_acc;
}

/*----------------------------------------*/
/*    UNIT TESTS FOR MMA862FCR1 CLASS   */
/*----------------------------------------*/

/**
 * @brief Test the constructor
 * 
 */
void MMA8652OnlineTest::MMA8652_Test()
{
    
}

/**
 * @brief Test the init function
 * 
 */
void MMA8652OnlineTest::init_Test()
{
    qDebug() << "Testing the init function";

    //check with incorrect setup
    QVERIFY2(m_acc->init(0x1F, 7, 0)==false, "Should return false if wrong devId given");

    //check the correct setup
    QVERIFY2(m_acc->init(0x1D, 7, 0)==true, "Check RPI define in config file");
}

/**
 * @brief Test the getDistance function
 * 
 */
void MMA8652OnlineTest::getData_Test()
{
    qDebug() << "Testing the getData function";

    accValues_t testData;
    QVERIFY2(m_acc->getData(&testData)==true, "Check RPI define in config file");
}

/**
 * @brief Test the recordStatic function
 * 
 */
void MMA8652OnlineTest::recordStatic_Test()
{
    qDebug() << "Testing the recordStatic function";

    QVERIFY2(m_acc->recordStatic()==true, "Check RPI define in config file");
}



/* run tests */
//QTEST_MAIN(MMA8652OnlineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    MMA8652OnlineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "MMA8652_Online_Test.moc"