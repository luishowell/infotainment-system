#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QSlider>
#include <QDial>

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
    QSlider *m_speedSlider;
    QSlider *m_fuelGauge;
    QDial *m_speedDial;
    void CreateLayout();
    bool canConnectionFlag;
};

#endif // DIAGNOSTICS_H