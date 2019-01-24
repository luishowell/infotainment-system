#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include "Timer.h"
#include "types.h"

class CANThread : public QThread
{
    Q_OBJECT

public:
    explicit CANThread();
    

private slots:
    void PublishDiagData();

signals:
    void CANPublishDiagTx(diagMsg_t* msg);

private:
    Timer *m_publishTimer;
    //obd2 *m_obd;
    diagMsg_t m_msg;
    void run();
};


#endif //CANTHREAD_H