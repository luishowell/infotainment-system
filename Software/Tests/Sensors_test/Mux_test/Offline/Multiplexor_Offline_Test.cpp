/**
 * @file Multiplexor_Offline_Test.cpp
 * @author Jamie Brown/Joe Walker
 * @brief Offline tests for the multiplexor class
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

using namespace std;

/**
 * @brief Offline unit tests for the multiplexor class.
 * 
 */

class MultiplexorOfflineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for multiplexor */
    void Multiplexor_Test();

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
void MultiplexorOfflineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief 
 * 
 */
void MultiplexorOfflineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief This method is called before each test case, creates a new multiplexor object
 * 
 */
void MultiplexorOfflineTest::init()
{
    qDebug() << "init";
    m_mux = new multiplexor();
}

/**
 * @brief This method is called after each test case, deletes the multiplexor object used in the previous test case
 * 
 */
void MultiplexorOfflineTest::cleanup()
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
void MultiplexorOfflineTest::Multiplexor_Test()
{
    
}



/* run tests */
//QTEST_MAIN(MultiplexorOfflineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    MultiplexorOfflineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "Multiplexor_Offline_Test.moc"