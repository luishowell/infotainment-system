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

#include "obd2.hpp"
#include "LoggerWindow.h"
#include "types.h"
#include "AccGauge.h"
#include "MMA8652FCR1.h"

#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QSlider>
#include <QDial>
#include <QQuickItem>
#include <QGroupBox>
#include <QLCDNumber>
#include <QPointer>
#include <QVector>
#include <QString>

class Diagnostics : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Diagnostics object
     * 
     * @param parent 
     * @param myObd 
     * @param acc 
     */
    explicit Diagnostics(QWidget *parent = 0, obd2* myObd = 0, MMA8652FCR1* acc = 0);
    /**
     * @brief Create a Layout object
     * 
     */
    void CreateLayout();
    
    obd2* obd;
    LoggerWindow *m_logWindow;
    
public slots:
    /**
     * @brief 
     * 
     */
    void StateChangeMainMenu();
    /**
     * @brief 
     * 
     * @param msg 
     */
    void DiagDataRx(diagMsg_t* msg);
    /**
     * @brief 
     * 
     * @param msg 
     */
    void AccDataRx(accValues_t* msg);
    /**
     * @brief 
     * 
     */
    void JourneyLogRequest();
    /**
     * @brief 
     * 
     * @param logParams 
     * @param start 
     */
    void LogRequestRx(QVector<QString>  logParams, bool start);
    /**
     * @brief 
     * 
     */
    void CloseLogWindow();
    /**
     * @brief 
     * 
     */
    void ShowRpmGauge();
    /**
     * @brief 
     * 
     */
    void ShowSpeedGauge();
    /**
     * @brief 
     * 
     */
    void ShowAirTempGauge();
    /**
     * @brief 
     * 
     */
    void ShowThrottleGauge();
    /**
     * @brief 
     * 
     */
    void ShowGearGauge();
    /**
     * @brief 
     * 
     */
    void ShowFuelPressureGauge();
    /**
     * @brief 
     * 
     */
    void ShowEngineRuntimeGauge();
    /**
     * @brief 
     * 
     */
    void ShowEngineLoadGauge();
    /**
     * @brief 
     * 
     */
    void ShowAccGauge();
    /**
     * @brief 
     * 
     */
    void ShowMe();

signals:
    /**
     * @brief 
     * 
     * @param req_state 
     * @param currentView 
     */
    void DisplayChange(state_t req_state, QWidget* currentView);
    /**
     * @brief 
     * 
     * @param dataRequested 
     * @param channel 
     */
    void NewChannelRequest(diagParams_t dataRequested, obd2Channel_t channel);
    /**
     * @brief 
     * 
     * @param logParams 
     * @param start 
     */
    void StartLogging(QVector<QString> logParams, bool start);

private:
    /**
     * @brief Create a Components object
     * 
     */
    void CreateComponents();
    /**
     * @brief 
     * 
     */
    void ConnectButtons();
    /**
     * @brief 
     * 
     * @param state 
     */
    void ButtonState(bool state);

    typedef struct currentDisplay{
            QObject *obj;
            QGroupBox *box;
            QLCDNumber *num;
        } currentDisplay_t;

    currentDisplay_t currentLeftChannel;
    currentDisplay_t currentRightChannel;

    
    //int logClicked;

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

    QPointer<AccGauge> m_accGauge;
    MMA8652FCR1* m_acc;

/*
    QObject *m_currentLeftObj;
    QObject *m_currentRightObj;
*/
    QPointer<QGroupBox> accBox;
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

    QPointer<QPushButton> m_rpmButton;
    QPointer<QPushButton> m_speedButton;
    QPointer<QPushButton> m_intakeAirTempButton;
    QPointer<QPushButton> m_throttleButton;
    QPointer<QPushButton> m_gearButton;
    QPointer<QPushButton> m_fuelPressureButton;
    QPointer<QPushButton> m_engineRuntimeButton;
    QPointer<QPushButton> m_engineLoadButton;
    QPointer<QPushButton> m_accButton;


    QPushButton *m_logButton;
    
    QQuickItem *speedo;

    
    
    
    bool canConnectionFlag;
};
//Q_DECLARE_METATYPE(std::vector<std::string>)

#endif // DIAGNOSTICS_H