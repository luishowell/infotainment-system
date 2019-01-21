#ifndef GUITHREAD_H
#define GUITHREAD_H

#include <QThread>

class GUIThread : public QThread
{
    Q_OBJECT

public:
    explicit GUIThread();
    void run();

};


#endif //GUITHREAD_H