/**
 * @file OBD2_Test.cpp
 * @author Jamie Brown/Luis Howell
 * @brief 
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

class OBD2Test: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for obd2 */
    void obd2_Test();
    void SendCmd_Test();
    void ScanPids_Test();
    void PrintSupportedPids_Test();
    void DecodeResponse_Test();
    void DecodedCmd_Test();
    void ReadDtc_Test();
    void DtcDesc_Test();
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
void OBD2Test::initTestCase()
{
    qDebug() << "initTestCase";
    //m_obd = new obd2("/dev/rfcomm0");
}

/**
 * @brief 
 * 
 */
void OBD2Test::cleanupTestCase()
{
    qDebug() << "cleanupTestCase";

}

/**
 * @brief 
 * 
 */
void OBD2Test::init()
{
    qDebug() << "init";
    m_obd = new obd2("/dev/rfcomm0");

}

/**
 * @brief 
 * 
 */
void OBD2Test::cleanup()
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
void OBD2Test::obd2_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QCOMPARE(m_obd->connected, true);
    delete m_obd;

    m_obd = new obd2("/dev");
    QCOMPARE(m_obd->connected, false);
    
    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::SendCmd_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->send_cmd("ATS0", true)=="OK");
    QVERIFY(m_obd->send_cmd("test", true)=="?");

    string response = m_obd->send_cmd("0100", true);
    QVERIFY(response.substr(0, 4)=="4100");

    response = m_obd->send_cmd("010C", true);
    QVERIFY(response.substr(0, 4)=="410C");

    response = m_obd->send_cmd("03", true);
    QVERIFY(response.substr(0, 2)=="43");

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::ScanPids_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    m_obd->scan_pids();
    QVERIFY(m_obd->supported_pids.size()>0);
    QVERIFY(m_obd->supported_pids[0]=="00");

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::PrintSupportedPids_Test()
{
   
}

/**
 * @brief 
 * 
 */
void OBD2Test::DecodeResponse_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->decode_response("41057B") == 83.0);    
    QVERIFY(m_obd->decode_response("410C1AF8") == 1726.0);    
    QVERIFY(m_obd->decode_response("test") == -999);  
    QVERIFY(m_obd->decode_response("43013300210010") == -999);   
    QVERIFY(m_obd->decode_response("4100") == -999);   
    QVERIFY(m_obd->decode_response("41") == -999);  
    QVERIFY(m_obd->decode_response("4105") == -999);  
    QVERIFY(m_obd->decode_response("010D") == -999);  
    QVERIFY(m_obd->decode_response("41057BC1") == -999); 

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::DecodedCmd_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->decoded_cmd("010C") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010C1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("test") ==  -999);
    QVERIFY(m_obd->decoded_cmd("5738") ==  -999);
    QVERIFY(m_obd->decoded_cmd("01") ==  -999);

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::ReadDtc_Test()
{

}

/**
 * @brief 
 * 
 */
void OBD2Test::DtcDesc_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->dtc_desc("P0010") ==  "A camshaft position actuator circuit (bank 1)");
    QVERIFY(m_obd->dtc_desc("B1636") ==  "Mirror Driver Right Circuit Open");
    QVERIFY(m_obd->dtc_desc("test") ==  "No DTC description");
    QVERIFY(m_obd->dtc_desc("756412") ==  "No DTC description");

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::Hex2int_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->hex2int("010D") == 269);  
    QVERIFY(m_obd->hex2int("0") == 0);  
    QVERIFY(m_obd->hex2int("test") == 0);  
    QVERIFY(m_obd->hex2int("-010D") == 0);  

    //delete m_obd;
}

/**
 * @brief 
 * 
 */
void OBD2Test::Int2hex_Test()
{
    //m_obd = new obd2("/dev/rfcomm0");

    QVERIFY(m_obd->int2hex(1)=="01");
    QVERIFY(m_obd->int2hex(0)=="00");
    QVERIFY(m_obd->int2hex(3697)=="E71");

    //delete m_obd;
}

/* run tests */
//QTEST_MAIN(OBD2Test);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    cout << "MAIN" << endl;

    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    OBD2Test tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "OBD2_Test.moc"