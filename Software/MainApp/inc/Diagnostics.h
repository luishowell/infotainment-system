/**
 * @file Diagnostics.h
 * @author Jamie Brown
 * @brief The main widget class for the diagnostics screen.
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
#include <QLabel>

/**
 * @brief Top level QWidget of the Diagnostics screen.
 * 
 */
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
     * @brief Sends request signal to change to the MainMenu.
     * 
     */
    void StateChangeMainMenu();

    /**
     * @brief Callback when diagnostics data is received from the CANWorker / CANThread.
     * 
     * @param msg 
     */
    void DiagDataRx(diagMsg_t* msg);

    /**
     * @brief Callback when accelerometer data is received from the AccWorker / AccThread.
     * 
     * @param msg 
     */
    void AccDataRx(accValues_t* msg);

    /**
     * @brief Callback when the logging button is pressed. Opens the LoggerWindow, resets if previously closed. 
     * 
     */
    void JourneyLogRequest();

    /**
     * @brief Callback when log parameters received from LoggingWindow. Emits signal to CANWorker to start logging. 
     * 
     * @param logParams QVector of QStrings including user requested pid codes. 
     * @param start Boolean indicating whether or not logging has started.
     */
    void LogRequestRx(QVector<QString>  logParams, bool start);

    /**
     * @brief Hides the LoggingWindow and resets it for next use. 
     * 
     */
    void CloseLogWindow();

    /**
     * @brief Displays the RPM gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowRpmGauge();

    /**
     * @brief Displays the speed gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowSpeedGauge();

    /**
     * @brief Displays the air temperature gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowAirTempGauge();

    /**
     * @brief Displays the throttle gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowThrottleGauge();

    /**
     * @brief Displays the current gear gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowGearGauge();

    /**
     * @brief Displays the fuel pressure gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowFuelPressureGauge();

    /**
     * @brief Displays the engine runtime gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowEngineRuntimeGauge();

    /**
     * @brief Displays the engine load gauge and requests its pid code to the CANWorker.
     * 
     */
    void ShowEngineLoadGauge();

    /**
     * @brief Displays the accelerometer gauge its data is acquired in a seperate thread to OBD2 data and is therefore not required to be requested.
     * 
     */
    void ShowAccGauge();

    /**
     * @brief Shows the window and the LoggerWindow if it is currently logging. 
     * 
     */
    void ShowMe();

private slots:

    /**
     * @brief turns the connection warning off and on
     * 
     */
    void WarningTimeout();
    
    void GaugeTimeout();

signals:
    /**
     * @brief Request to change the current view. 
     * 
     * @param req_state state_t, The requested view. 
     * @param currentView Pointer to this QWidget.
     */
    void DisplayChange(state_t req_state, QWidget* currentView);

    /**
     * @brief Requests a new parameter for a given OBD2 channel. 
     * 
     * @param dataRequested Requested diagnostics data. 
     * @param channel Channel to obtain data (A or B).
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
     * @brief Create the buttons, sliders etc. 
     * 
     */
    void CreateComponents();

    /**
     * @brief Connects signals and slots for the buttons. 
     * 
     */
    void ConnectButtons();

    /**
     * @brief Sets all buttons to a requested state (enabled/disabled). 
     * 
     * @param state Boolean of the required state. 
     */
    void ButtonState(bool state);

    /**
     * @brief Enables all selection buttons
     * 
     */
    void EnableButtons();

    /**
     * @brief Structure containing objects for a displayed diagnostics parameter. 
     * 
     */
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
    QPointer<AccGauge> m_accGauge;
    MMA8652FCR1* m_acc;
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
    bool canConnectionFlag = true;
    QPointer<QLabel> m_CANWarning;
    QPointer<QTimer> m_warningTimer;
    bool m_timedout;
    bool m_fancyMode;
    bool m_enableGauge;
    QPointer<QTimer> m_gaugeDelay;
};
//Q_DECLARE_METATYPE(std::vector<std::string>)

#endif // DIAGNOSTICS_H