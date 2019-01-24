#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QSlider>
#include <QDial>
#include <QQuickItem>

#include "types.h"

class Diagnostics : public QWidget
{
    Q_OBJECT
public:
    explicit Diagnostics(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();
    void DiagDataRx(diagMsg_t* msg);


signals:
    void DisplayChange(state_t req_state, QWidget* currentView);

private:
    QPushButton *m_homeButton;
    QWidget *m_speedometer;
    QObject *m_speedObject;
    QWidget *m_fuelGauge;
    QObject *m_fuelObject;
    QWidget *m_rpmGauge;
    QObject *m_rpmObject;
    
    QQuickItem *speedo;

    void CreateLayout();
    void CreateComponents();
    bool canConnectionFlag;
};

#endif // DIAGNOSTICS_H