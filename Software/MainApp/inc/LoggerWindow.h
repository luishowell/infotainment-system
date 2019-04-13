/**
 * @file LoggerWindow.h
 * @author Jamie Brown
 * @brief The main widget class for the logger window that is shown when the journey logger button is clicked.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include "types.h"

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPointer>
#include <QLabel>
#include <QTimer>
#include <QVector>
#include <QString>
#include <vector>
#include <string>

/**
 * @brief Data logger window that is shown by the Diagnostics screen.
 * 
 */
class LoggerWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Logger Window object
     * 
     * @param supportedPids A vector of strings containing the supported pids for a given vehicle. 
     * @param parent The parent widget.
     */
    explicit LoggerWindow(std::vector<std::string> supportedPids, QWidget* parent = 0);

    /**
     * @brief Unchecks and enables relevant buttons. Should be called after the window is closed. 
     * 
     */
    void reset();

    /**
     * @brief Informs caller whether or not logging is currently occuring.
     * 
     * @return true Currently logging.
     * @return false Not logging.
     */
    bool isLogging() const;

    /**
     * @brief Shows this widget.
     * 
     */
    void ShowMe();

    QVector<QString> supportedPids;
    QVector<QString> selectedParams;

public slots:
    /**
     * @brief Emits a logging request to CANWorker/CANThread and disables all buttons.
     * 
     */
    void StartLogging();

    /**
     * @brief Emits a stop logging request to CANWorker/CANThread and enables all buttons. 
     * 
     */
    void StopLogging();

    /**
     * @brief Callback when a logging parameter checkbox is clicked. Adds or removes the requested parameter to a list.
     * 
     */
    void OnClicked();

    /**
     * @brief Callback for close button, emits a close signal to the Diagnostics widget.
     * 
     */
    void CloseWindow();

private slots:
    /**
     * @brief Changes the QLabel displayed while logging with a scrolling full-stop. (LOGGING...)
     * 
     */
    void UpdateLogMsg();

signals:
    /**
     * @brief Transmits a request to start or stop logging requested parameters.
     * 
     * @param logParams A QVector of QStrings containing the requested parameters as pid codes. 
     * @param start Boolean indicating whether to start or stop logging.
     */
    void LogRequestTx(QVector<QString> logParams, bool start);

    /**
     * @brief Transmits a request to close the window. 
     * 
     */
    void CloseRequest();

private:
    /**
     * @brief Removes a requested parameter from the list. 
     * 
     * @param param Parameter as a pid code. 
     */
    void RemoveParameter(QString param);

    /**
     * @brief Connects all buttons to respective slot callbacks. 
     * 
     */
    void ConnectButtons();

    /**
     * @brief Disables all parameter checkboxes.
     * 
     */
    void DisableButtons();

    /**
     * @brief Enables all parameter checkboxes.
     * 
     */
    void EnableButtons();

    QCheckBox *m_speedButton;
    QCheckBox *m_rpmButton;
    QCheckBox *m_fuelPressureButton;
    QCheckBox *m_gearButton;
    QCheckBox *m_intakeAirTempButton;
    QCheckBox *m_engineRuntimeButton;
    QCheckBox *m_engineLoadButton;
    QCheckBox *m_throttleButton;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_closeButton;

    QVBoxLayout *selectLeft;
    QVBoxLayout *selectRight;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    QPointer<QLabel> m_loggingMsg;
    QPointer<QLabel> m_stoppedMsg;
    QPointer<QLabel> m_selectMsg;
    QPointer<QTimer> m_msgTimer;
    int m_msgCount = 0;
    bool m_isLogging = false;
    bool m_available = false;

    std::vector<std::string> m_pids;
};

#endif // MAINMENU_H