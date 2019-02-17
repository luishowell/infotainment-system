#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include <string>
#include "config.h"
#include "Timer.h"
#include "types.h"
#include "CANWorker.h"

#ifndef GUI_TEST
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

private:
    void run();

};


#endif //CANTHREAD_H
