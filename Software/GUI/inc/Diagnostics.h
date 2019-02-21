/**
 * @file Diagnostics.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QSlider>
#include <QDial>
#include <QQuickItem>
#include <QGroupBox>
#include <QLCDNumber>

#ifndef GUI_TEST
#include "obd2.hpp"
#endif

#include "types.h"

class Diagnostics : public QWidget
{
    Q_OBJECT
public:
    explicit Diagnostics(QWidget *parent = 0);
    #ifndef GUI_TEST
    obd2* obd;
    #endif
    
public slots:
    void StateChangeMainMenu();
    void DiagDataRx(diagMsg_t* msg);
    void JourneyLogRequest();
    void ShowRpmGauge();
    void ShowSpeedGauge();
    void ShowAirTempGauge();
    void ShowThrottleGauge();
    void ShowGearGauge();
    void ShowFuelPressureGauge();
    void ShowEngineRuntimeGauge();
    void ShowEngineLoadGauge();
 

signals:
    void DisplayChange(state_t req_state, QWidget* currentView);
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    void StartLogging();

private:
    
    typedef struct currentDisplay{
            QObject *obj;
            QGroupBox *box;
            QLCDNumber *num;
        } currentDisplay_t;

    currentDisplay_t currentLeftChannel;
    currentDisplay_t currentRightChannel;

    QPushButton *m_homeButton;
    QWidget *m_speedometer;
    QObject *m_speedObject;
    QLCDNumber *m_speedLCD;
    QWidget *m_airTempGauge;
    QObject *m_airTempObject;
    QLCDNumber *m_airTempLCD;
    QWidget *m_rpmGauge;
    QObject *m_rpmObject;
    QLCDNumber *m_rpmLCD;
    QWidget *m_throttleGauge;
    QObject *m_throttleObject;
    QLCDNumber *m_throttleLCD;
    QWidget *m_gearGauge;
    QObject *m_gearObject;
    QLCDNumber *m_gearLCD;
    QWidget *m_fuelPressureGauge;
    QObject *m_fuelPressureObject;
    QLCDNumber *m_fuelPressureLCD;
    QWidget *m_engineRuntimeGauge;
    QObject *m_engineRuntimeObject;
    QLCDNumber *m_engineRuntimeLCD;
    QWidget *m_engineLoadGauge;
    QObject *m_engineLoadObject;
    QLCDNumber *m_engineLoadLCD;



/*
    QObject *m_currentLeftObj;
    QObject *m_currentRightObj;
*/
    QGroupBox* speedBox;
    QGroupBox* rpmBox;
    QGroupBox* selectBox;
    QGroupBox* airTempBox;
    QGroupBox* throttleBox;
    QGroupBox* gearBox;
    QGroupBox* fuelPressureBox;
    QGroupBox* engineRuntimeBox;
    QGroupBox* engineLoadBox;



    QGroupBox *currentLeftGauge;
    QGroupBox *currentRightGauge;

    /* parameter selection buttons */
    QPushButton *m_rpmButton;
    QPushButton *m_speedButton;
    QPushButton *m_intakeAirTempButton;
    QPushButton *m_throttleButton;
    QPushButton *m_gearButton;
    QPushButton *m_fuelPressureButton;
    QPushButton *m_engineRuntimeButton;
    QPushButton *m_engineLoadButton;


    QPushButton *m_logButton;

    
    
    QQuickItem *speedo;

    void CreateLayout();
    void CreateComponents();
    void ConnectButtons();
    diagParams_t HashPID(std::string pidString);
    
    bool canConnectionFlag;
};

#endif // DIAGNOSTICS_H