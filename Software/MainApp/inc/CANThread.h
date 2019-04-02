/** @brief Thread that obtains data from the OBD2 bus on a periodic basis
 * 
 * @author Jamie Brown
 * @date February 2019
 * */

#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include <string>
#include "config.h"
#include "types.h"

#ifndef GUI_TEST
#include "obd2.hpp"
#endif

class CANThread : public QThread
{
    Q_OBJECT

public:
    explicit CANThread();
    ~CANThread();
    

private slots:
    void PublishDiagData();

signals:
    void CANPublishDiagTx(diagMsg_t* msg);
    void CANPublishLogTx();

private:
    //string m_dataRequest;
    void DummyData();
    void run();
    diagMsg_t m_msg;

#ifndef GUI_TEST
    obd2 *m_obd;
#endif
};


#endif //CANTHREAD_H