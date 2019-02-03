#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QSlider>
#include <QDial>
#include <QQuickItem>
#include <QGroupBox>

#include "types.h"

class Diagnostics : public QWidget
{
    Q_OBJECT
public:
    explicit Diagnostics(QWidget *parent = 0);
    
public slots:
    void StateChangeMainMenu();
    void DiagDataRx(diagMsg_t* msg);
    void JourneyLogRequest();
    void ShowRpmGauge();
    void ShowSpeedGauge();
    void ShowAirTempGauge();
    void ShowThrottleGauge();
    

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void StartLogging();

private:
    
    typedef struct currentDisplay{
            QObject *obj;
            QGroupBox *box;
        } currentDisplay_t;

    currentDisplay_t currentLeftChannel;
    currentDisplay_t currentRightChannel;

    QPushButton *m_homeButton;
    QWidget *m_speedometer;
    QObject *m_speedObject;
    QWidget *m_airTempGauge;
    QObject *m_airTempObject;
    QWidget *m_rpmGauge;
    QObject *m_rpmObject;
    QWidget *m_throttleGauge;
    QObject *m_throttleObject;

/*
    QObject *m_currentLeftObj;
    QObject *m_currentRightObj;
*/
    QGroupBox* speedBox;
    QGroupBox* rpmBox;
    QGroupBox* selectBox;
    QGroupBox* airTempBox;
    QGroupBox* throttleBox;
    QGroupBox *currentLeftGauge;
    QGroupBox *currentRightGauge;

    QPushButton *m_rpmButton;
    QPushButton *m_speedButton;
    QPushButton *m_intakeAirTempButton;
    QPushButton *m_throttleButton;
    QPushButton *m_logButton;

    
    
    QQuickItem *speedo;

    void CreateLayout();
    void CreateComponents();
    void ConnectButtons();

    bool canConnectionFlag;
};

#endif // DIAGNOSTICS_H