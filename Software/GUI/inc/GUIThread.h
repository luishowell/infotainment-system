/**
 * @file GUIThread.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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