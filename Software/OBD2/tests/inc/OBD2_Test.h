#include <QtTest/QtTest>
#include "obd2.hpp"

class OBD2Test: public QObject
{
    Q_OBJECT
private slots:
    void obd2Test();
    void send_cmdTest();
    void scan_pidsTest();
    void print_supported_pidsTest();
    void decode_responseTest();
    void decoded_cmdTest();
private:
    obd2* m_obd;
};



