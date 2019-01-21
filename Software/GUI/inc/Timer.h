#ifndef TIMER_H
#define TIMER_H

#include <QtCore>
#include <QObject>

class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(int msecs);
    QTimer *timer;

public slots:
    void OnTimerExpired();

};


#endif //TIMER_H