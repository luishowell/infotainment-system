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
/*     UNIT TESTS FOR MULTIPLEXOR CLASS   */
/*----------------------------------------*/

/* constructor test */
void OBD2Test::obd2Test()
{
    m_OBD = new obd2("/dev/rfcomm0");
    QCOMPARE(m_OBD->connected, true);
    delete m_OBD;

    m_OBD = new obd2("/dev");
    QCOMPARE(m_OBD->connected, false);
    
    /* m_OBD will be deleted by cleanup function */
}

void OBD2Test::send_cmdTest()
{
  
}

void OBD2Test::scan_pidsTest()
{
  
}

void OBD2Test::print_supported_pidsTest()
{
   
}

void OBD2Test::decode_responseTest()
{
  
}

void OBD2Test::decoded_cmdTest()
{
    QVERIFY(m_obd->decoded_cmd("010D") > 0 );
    QVERIFY(m_obd->decoded_cmd("010C") > 0 );
    QVERIFY(m_obd->decoded_cmd("010F") > 0 );
    QVERIFY(m_obd->decoded_cmd("0111") > 0 );
    QVERIFY(m_obd->decoded_cmd("5738") ==  -999);
}

QTEST_MAIN(OBD2Test)
#include "obd2test.moc"