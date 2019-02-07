#include <QtTest/QtTest>
#include <iostream>
#include <string>
#include "obd2.hpp"

using namespace std;

class OBD2Test: public QObject
{
    Q_OBJECT
private slots:
    void Obd2_Test();
    void SendCmdTest();
    void ScanPids_Test();
    void PrintSupportedPids_Test();
    void DecodeResponse_Test();
    void DecodedCmd_Test();
    void ReadDtc_Test();
    void DtcDesc_Test();
    void Hex2int_Test();
    void Int2hex_Test();
private:
    obd2* m_obd;
};

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void OBD2Test::initTestCase()
{
}

void OBD2Test::cleanupTestCase()
{
}

/* called before each test case */
void OBD2Test::init()
{
    m_OBD = new obd2("/dev/rfcomm0");
}

/* called after each test case */
void OBD2Test::cleanup()
{
    delete m_OBD;
}

/*----------------------------------------*/
/*     UNIT TESTS FOR OBD2 CLASS          */
/*----------------------------------------*/

/* constructor test */
void OBD2Test::obd2Test()
{
    
    QCOMPARE(m_OBD->connected, true);
    delete m_OBD;

    m_OBD = new obd2("/dev");
    QCOMPARE(m_OBD->connected, false);
    
    /* m_OBD will be deleted by cleanup function */
}

void OBD2Test::SendCmd_Test()
{
    QVERIFY(m_obd->send_cmd("ATS0", true)=="OK");
    QVERIFY(m_obd->send_cmd("test", true)=="?");

    string response = m_obd->send_cmd("0100", true);
    QVERIFY(response.substr(0, 4)=="4100");

    string response = m_obd->send_cmd("010C", true);
    QVERIFY(response.substr(0, 4)=="410C");

    string response = m_obd->send_cmd("03", true);
    QVERIFY(response.substr(0, 2)=="43");
}

void OBD2Test::ScanPids_Test()
{
    m_obd->scan_pids();
    QVERIFY(m_obd->supported_pids.size()>0);
    QVERIFY(m_obd->supported_pids[0]=="00";
}

void OBD2Test::PrintSupportedPids_Test()
{
   
}

void OBD2Test::DecodeResponse_Test()
{
    QVERIFY(m_obd->decode_response("41057B") == 83.0);    
    QVERIFY(m_obd->decode_response("410C1AF8") == 1726.0);    
    QVERIFY(m_obd->decode_response("test") == -999);  
    QVERIFY(m_obd->decode_response("43013300210010") == -999);   
    QVERIFY(m_obd->decode_response("4100") == -999);   
    QVERIFY(m_obd->decode_response("41") == -999);  
    QVERIFY(m_obd->decode_response("4105") == -999);  
    QVERIFY(m_obd->decode_response("41057") == -999);  
    QVERIFY(m_obd->decode_response("010D") == -999);  
    QVERIFY(m_obd->decode_response("41057BC1") == -999); 
}

void OBD2Test::DecodedCmd_Test()
{
    QVERIFY(m_obd->decoded_cmd("010C") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010C1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("010D1") >= 0 );
    QVERIFY(m_obd->decoded_cmd("test") ==  -999);
    QVERIFY(m_obd->decoded_cmd("5738") ==  -999);
    QVERIFY(m_obd->decoded_cmd("01") ==  -999);
}

void OBD2Test::ReadDtc_Test()
{

}

void OBD2Test::DtcDesc_Test()
{
    QVERIFY(m_obd->dtc_desc("P0010") ==  "A camshaft position actuator circuit (bank 1)");
    QVERIFY(m_obd->dtc_desc("B1636") ==  "Mirror Driver Right Circuit Open");
    QVERIFY(m_obd->dtc_desc("test") ==  "No DTC description");
    QVERIFY(m_obd->dtc_desc("756412") ==  "No DTC description");
}

void OBD2Test::Hex2int_Test()
{
    QVERIFY(m_obd->hex2int("010D") == 269);  
    QVERIFY(m_obd->hex2int("0") == 0);  
    QVERIFY(m_obd->hex2int("test") == 0);  
    QVERIFY(m_obd->hex2int("-010D") == 0);  
}

void OBD2Test::Int2hex_Test()
{
    QVERIFY(m_obd->int2hex(1)=="01");
    QVERIFY(m_obd->int2hex(0)=="00");
    QVERIFY(m_obd->int2hex(3697)=="E71");
}

/* run tests */
//QTEST_MAIN(OBD2Test);
QT_BEGIN_NAMESPACE
QTEST_ADD_GPU_BLACKLIST_SUPPORT_DEFS
QT_END_NAMESPACE
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    OBD2Test tc;
    QTEST_SET_MAIN_SOURCE_PATH
    return QTest::qExec(&tc, argc, argv);
}
#include "obd2test.moc"