/**
 * @file LoggerWindow.h
 * @author Jamie Brown
 * @brief 
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef LOGGERWINDOW_H
#define LOGGERWINDOW_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPointer>
#include <QLabel>
#include <QTimer>
#include "types.h"
#include <vector>
#include <string>
#include <QVector>
#include <QString>

class LoggerWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Logger Window object
     * 
     * @param supportedPids 
     */
    explicit LoggerWindow(std::vector<std::string> supportedPids);

    /**
     * @brief 
     * 
     */
    void reset();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool isLogging() const;

    /**
     * @brief 
     * 
     */
    void ShowMe();

    QVector<QString> supportedPids;
    QVector<QString> selectedParams;

public slots:
    /**
     * @brief 
     * 
     */
    void StartLogging();

    /**
     * @brief 
     * 
     */
    void StopLogging();

    /**
     * @brief 
     * 
     */
    void OnClicked();

    /**
     * @brief 
     * 
     */
    void CloseWindow();

private slots:
    /**
     * @brief 
     * 
     */
    void UpdateLogMsg();

signals:
    /**
     * @brief 
     * 
     * @param start 
     */
    void LogRequestTx(QVector<QString>logParams, bool start);

    /**
     * @brief 
     * 
     */
    void CloseRequest();

private:
    /**
     * @brief 
     * 
     * @param param 
     */
    void RemoveParameter(QString param);

    /**
     * @brief 
     * 
     */
    void ConnectButtons();

    /**
     * @brief 
     * 
     * @param name 
     * @return diagParams_t 
     */
    diagParams_t HashButtonName(QString name);

    /**
     * @brief 
     * 
     */
    void DisableButtons();

    /**
     * @brief 
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