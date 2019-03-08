/**
 * @file OBD2_Offline_Test.cpp
 * @author Jamie Brown/Luis Howell
 * @brief 
 * @version 0.1
 * @date 2019-03-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <QtTest/QtTest>
#include <iostream>
#include <string>
#include <obd2.hpp>

using namespace std;

class OBD2OfflineTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for offline obd2 */
    void DecodeResponse_Test();
    void DtcDesc_Test();
    void PidDesc_Test();
    void Hex2int_Test();
    void Int2hex_Test();    

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
void OBD2OfflineTest::initTestCase()
{
    qDebug() << "initTestCase";
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::init()
{
    qDebug() << "init";
    m_obd = new obd2("/dev/rfcomm0");
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::cleanup()
{
    qDebug() << "cleanup";
    delete m_obd;
}

/*----------------------------------------*/
/*     UNIT TESTS FOR OBD2 CLASS          */
/*----------------------------------------*/

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::DecodeResponse_Test()
{
    QVERIFY(m_obd->decode_response("41057B") == 83.0);    
    QVERIFY(m_obd->decode_response("410C1AF8") == 1726.0);    
    QVERIFY(m_obd->decode_response("test") == -999);  
    QVERIFY(m_obd->decode_response("43013300210010") == -999);   
    QVERIFY(m_obd->decode_response("4100") == -999);   
    QVERIFY(m_obd->decode_response("41") == -999);  
    QVERIFY(m_obd->decode_response("4105") == -999);  
    QVERIFY(m_obd->decode_response("010D") == -999);  
    QVERIFY(m_obd->decode_response("41057BC1") == -999); 
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::DtcDesc_Test()
{
    QVERIFY(m_obd->dtc_desc("P0010") ==  "A camshaft position actuator circuit (bank 1)");
    QVERIFY(m_obd->dtc_desc("B1636") ==  "Mirror Driver Right Circuit Open");
    QVERIFY(m_obd->dtc_desc("test") ==  "No DTC description");
    QVERIFY(m_obd->dtc_desc("756412") ==  "No DTC description");    
}

void OBD2OfflineTest::PidDesc_Test()
{
    QVERIFY(m_obd->pid_desc("00") ==  "PIDs supported [01 - 20]");
    QVERIFY(m_obd->pid_desc("10") ==  "MAF air flow rate");
    QVERIFY(m_obd->pid_desc("9D") ==  "Engine Fuel Rate");
    QVERIFY(m_obd->pid_desc("test") ==  "No PID description"); 
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::Hex2int_Test()
{
    QVERIFY(m_obd->hex2int("010D") == 269);  
    QVERIFY(m_obd->hex2int("0") == 0);  
    QVERIFY(m_obd->hex2int("test") == 0);  
    QVERIFY(m_obd->hex2int("-010D") == 0);  
}

/**
 * @brief 
 * 
 */
void OBD2OfflineTest::Int2hex_Test()
{
    QVERIFY(m_obd->int2hex(1)=="01");
    QVERIFY(m_obd->int2hex(0)=="00");
    QVERIFY(m_obd->int2hex(3697)=="E71");
    QVERIFY(m_obd->int2hex(-10)=="0A");
}

/* run tests */
//QTEST_MAIN(OBD2OfflineTest);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    cout << "MAIN" << endl;

    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    OBD2OfflineTest tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "OBD2_Offline_Test.moc"


