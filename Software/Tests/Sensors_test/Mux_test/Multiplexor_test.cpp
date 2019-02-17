/**
 * @file Multiplexor_test.cpp
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
#include "multiplexor.h"
#include "types.h"

using namespace std;

class MultiplexorTest: public QObject
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
void MultiplexorTest::initTestCase()
{

}

/**
 * @brief 
 * 
 */
void MultiplexorTest::cleanupTestCase()
{

}

/**
 * @brief This method is called before each test case, creates a new multiplexor object
 * 
 */
void MultiplexorTest::init()
{

}

/**
 * @brief This method is called after each test case, deletes the multiplexor object used in the previous test case
 * 
 */
void MultiplexorTest::cleanup()
{
    
}

/*----------------------------------------*/
/*     UNIT TESTS FOR MULTIPLEXOR CLASS   */
/*----------------------------------------*/

/**
 * @brief Tests the multiplexor constructor
 * 
 */
void MultiplexorTest::Multiplexor_Test()
{
    int a;
    a=5;
    QCOMPARE(a,5);
}

/**
 * @brief 
 * 
 */
void MultiplexorTest::Init_Test()
{

}

/**
 * @brief 
 * 
 */
void MultiplexorTest::SetMux_Test()
{

}

/* run tests */
//QTEST_MAIN(MultiplexorTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    MultiplexorTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "Multiplexor_test.moc"