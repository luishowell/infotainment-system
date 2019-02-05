#include <iostream>
#include "OBD2Test.h"

using namespace std;

/*----------------------------------------*/
/*              TEST SETUP                */
/*----------------------------------------*/

void OBD2Test::initTestCase()
{
    cout<<"STARTING OBD2 UNIT TESTS"<<endl;
}

void OBD2Test::cleanupTestCase()
{
    cout<<"FINISHED OBD2 UNIT TESTS"<<endl;
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
  
}

void OBD2Test::ScanPids_Test()
{
  
}

void OBD2Test::PrintSupportedPids_Test()
{
   
}

void OBD2Test::DecodeResponse_Test()
{
  
}

void OBD2Test::DecodedCmd_Test()
{
    QVERIFY(m_obd->decoded_cmd("010D") > 0 );
    QVERIFY(m_obd->decoded_cmd("010C") > 0 );
    QVERIFY(m_obd->decoded_cmd("010F") > 0 );
    QVERIFY(m_obd->decoded_cmd("0111") > 0 );
    QVERIFY(m_obd->decoded_cmd("5738") ==  -999);
}

void OBD2Test::ReadDtc_Test()
{

}

void OBD2Test::DtcDesc_Test()
{

}


QTEST_MAIN(OBD2Test)
#include "obd2test.moc"