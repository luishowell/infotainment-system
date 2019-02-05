#include <QtTest/QtTest>
#include "obd2.hpp"

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
private:
    obd2* m_obd;
};



