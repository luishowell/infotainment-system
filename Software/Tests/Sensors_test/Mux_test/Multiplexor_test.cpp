#include <QtTest/QtTest>
#include <iostream>
//#include "multiplexor.h"
//#include "types.h"

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
    //multiplexor *m_mux;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void MultiplexorTest::initTestCase()
{
    //cerr << "STARTING UNIT TESTS FOR MULTIPLEXOR" << endl;
}

void MultiplexorTest::cleanupTestCase()
{
    //cerr << "FINISHED UNIT TESTS FOR MULTIPLEXOR" << endl;
}

/* called before each test case */
void MultiplexorTest::init()
{

}

/* called after each test case */
void MultiplexorTest::cleanup()
{
    
}

/*----------------------------------------*/
/*     UNIT TESTS FOR MULTIPLEXOR CLASS   */
/*----------------------------------------*/

/* constructor test */
void MultiplexorTest::Multiplexor_Test()
{
    int a;
    a=5;
    QCOMPARE(a,5);
}

void MultiplexorTest::Init_Test()
{

}

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