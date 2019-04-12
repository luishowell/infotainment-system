/**
 * @file MMA8652_Offline_Test.cpp
 * @author Joe Walker
 * @brief Offline tests for the MMA8652 class
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

using namespace std;

/**
 * @brief Offline tests for the MMA8652FCR1 class.
 * 
 */

class MMA8652OfflineTest: public QObject
{
    Q_OBJECT

private slots:
    /* unit tests for mma8652 */
    void MMA8652_Test();
    void init_Test();
    void getData_Test();
    void recordStatic_Test();
    void twosComp_Test();

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
void MMA8652OfflineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief 
 * 
 */
void MMA8652OfflineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief 
 * 
 */
void MMA8652OfflineTest::init()
{
    qDebug() << "init";
    m_acc = new MMA8652FCR1();
}

/**
 * @brief 
 * 
 */
void MMA8652OfflineTest::cleanup()
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
void MMA8652OfflineTest::MMA8652_Test()
{
    
}

/**
 * @brief Test the init function
 * 
 */
void MMA8652OfflineTest::init_Test()
{
    qDebug() << "Testing the init function";

    QVERIFY2(m_acc->init(0x1D, 7, 0)==false, "Check RPI define in config file");
}

/**
 * @brief Test the getDistance function
 * 
 */
void MMA8652OfflineTest::getData_Test()
{
    qDebug() << "Testing the getData function";

    accValues_t testData;
    QVERIFY2(m_acc->getData(&testData)==false, "Check RPI define in config file");
}

/**
 * @brief Test the recordStatic function
 * 
 */
void MMA8652OfflineTest::recordStatic_Test()
{
    qDebug() << "Testing the recordStatic function";

    QVERIFY2(m_acc->recordStatic()==false, "Check RPI define in config file");
}

/**
 * @brief Test the twos complement function
 * 
 */
void MMA8652OfflineTest::twosComp_Test()
{
    qDebug() << "Testing the twosComp function";

    //test the 8-bit version
    QVERIFY2(m_acc->twosComp(0xFF)==-0.0625, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x00)==0, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x7F)==7.9375, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x80)==-8, "Incorrect twos complement conversion");

    //test the 12-bit version
    QVERIFY2(m_acc->twosComp(0xFF, 0x30)==-0.05078125, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x00, 0x30)==0.01171875, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x7F, 0x30)==7.94921875, "Incorrect twos complement conversion");
    QVERIFY2(m_acc->twosComp(0x80, 0x30)==-7.98828125, "Incorrect twos complement conversion");
}

/* run tests */
//QTEST_MAIN(MMA8652OfflineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    MMA8652OfflineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "MMA8652_Offline_Test.moc"