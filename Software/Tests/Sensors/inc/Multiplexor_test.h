#include <QtTest/QtTest>
#include "multiplexor.h"

class MultiplexorTest: public QObject
{
    Q_OBJECT
private slots:
    /* unit tests for multiplexor */
    void Multiplexor_Test();
    void Init_Test();
    void SetMux_Test();

private:
    multiplexor *m_mux;
};
