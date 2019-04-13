/**
 * @file Multiplexor_Online_Test.cpp
 * @author Jamie Brown/Joe Walker
 * @brief Online tests for the multiplexor class
 * @version 0.2
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include "multiplexor.h"
#include "types.h"
#include "config.h"

using namespace std;

/**
 * @brief Online unit tests for the multiplexor class.
 * 
 */

class MultiplexorOnlineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for multiplexor */
    void Multiplexor_Test();
    void Init_Test();
    void SetMux_Test();

    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();
private:
    multiplexor *m_mux;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void MultiplexorOnlineTest::initTestCase()
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
void MultiplexorOnlineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief This method is called before each test case, creates a new multiplexor object
 * 
 */
void MultiplexorOnlineTest::init()
{
    qDebug() << "init";
    m_mux = new multiplexor();
}

/**
 * @brief This method is called after each test case, deletes the multiplexor object used in the previous test case
 * 
 */
void MultiplexorOnlineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_mux;
}

/*----------------------------------------*/
/*     UNIT TESTS FOR MULTIPLEXOR CLASS   */
/*----------------------------------------*/

/**
 * @brief Tests the multiplexor constructor
 * 
 */
void MultiplexorOnlineTest::Multiplexor_Test()
{
    
}

/**
 * @brief Tests the init function when not on RPI
 * 
 */
void MultiplexorOnlineTest::Init_Test()
{
    qDebug() << "Testing the init function";
    QVERIFY2(m_mux->init(23, 22, 21)==true, "Check RPI define in config file");
}

/**
 * @brief Tests the set_mux function when not on RPI
 * 
 */
void MultiplexorOnlineTest::SetMux_Test()
{
    qDebug() << "Testing the set_mux function";

    //check with a valid value
    QVERIFY2(m_mux->set_mux(1)==true, "Check RPI define in config file");

    //check with a invalid value
    QVERIFY2(m_mux->set_mux(12)==false, "Should report multiplexor error");
}

/* run tests */
//QTEST_MAIN(MultiplexorOnlineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    MultiplexorOnlineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "Multiplexor_Online_Test.moc"