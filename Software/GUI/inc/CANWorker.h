#ifndef CANWORKER_H
#define CANWORKER_H

#include <QObject>
#include <string>
#include "config.h"
#include "Timer.h"
#include "types.h"

#ifndef GUI_TEST
#include "obd2.hpp"
#endif

class CANWorker : public QObject
{
    Q_OBJECT

public:
    explicit CANWorker();
    ~CANWorker();
     diagMsg_t ObdMsg;
     QTimer *diagTimer;
    

private slots:
    void GetDiagData();
    void PublishDiagData();
    void GetLogData();
    void PublishLogData();
    void OnNewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);

signals:
    void CANPublishDiagTx(diagMsg_t* msg);
    void CANPublishLogTx();

private:
    //string m_dataRequest;
    void DummyData();
    bool m_running;
    
   

#ifndef GUI_TEST
    obd2 *m_obd;
#endif
};


#endif //CANWORKER_H
