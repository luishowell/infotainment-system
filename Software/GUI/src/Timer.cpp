#include "Timer.h"
#include <QtCore>
#include <stdio.h>

Timer::Timer(int msecs)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimerExpired()));

    timer->start(msecs);
}

void Timer::OnTimerExpired()
{
    printf("Timer expired\n");
}