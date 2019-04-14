/**
 * @file OBD2_Online_Test.cpp
 * @author Jamie Brown/Luis Howell
 * @brief Implementation of online tests for the obd2 class
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include <string>
#include <obd2.hpp>

using namespace std;

/**
 * @brief Online tests for the obd2 class.
 * 
 */

class OBD2OnlineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for online obd2 */
    void obd2_Test();
    void SendCmd_Test();
    void ScanPids_Test();
    void DecodedCmd_Test();

    /* hooks */
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private:
    obd2* m_obd;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::init()
{
    qDebug() << "init";
    m_obd = new obd2("/dev/rfcomm0");
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_obd;
}

/*----------------------------------------*/
/*     UNIT TESTS FOR OBD2 CLASS          */
/*----------------------------------------*/

/**
 * @brief Tests the OBD2 class constructor
 * 
 */
void OBD2OnlineTest::obd2_Test()
{
    QCOMPARE(m_obd->connected, true);
    delete m_obd;

    m_obd = new obd2("/dev");
    QCOMPARE(m_obd->connected, false);
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::SendCmd_Test()
{
    QVERIFY(m_obd->send_cmd("ATS0", true)=="OK");
    QVERIFY(m_obd->send_cmd("test", true)=="?");

    string response = m_obd->send_cmd("0100", true);
    QVERIFY(response.substr(0, 4)=="4100");

    response = m_obd->send_cmd("010C", true);
    QVERIFY(response.substr(0, 4)=="410C");

    response = m_obd->send_cmd("03", true);
    QVERIFY(response.substr(0, 2)=="43");
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::ScanPids_Test()
{
    m_obd->scan_pids();
    QVERIFY(m_obd->supported_pids.size()>0);
    QVERIFY(m_obd->supported_pids[0]=="00");
}

/**
 * @brief 
 * 
 */
void OBD2OnlineTest::DecodedCmd_Test()
{
    QVERIFY(m_obd->decoded_cmd("010C") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010C1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("test") ==  -999);
    QVERIFY(m_obd->decoded_cmd("5738") ==  -999);
    QVERIFY(m_obd->decoded_cmd("01") ==  -999);
}

/* run tests */
//QTEST_MAIN(OBD2OnlineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    cout << "MAIN" << endl;

    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    OBD2OnlineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "OBD2_Online_Test.moc"