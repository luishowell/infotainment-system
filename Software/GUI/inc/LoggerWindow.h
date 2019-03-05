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
#include "types.h"
#include <vector>
#include <string>
#include <QVector>
#include <QString>

class LoggerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoggerWindow(QVector<QString> supportedPids);
    QVector<QString> supportedPids;
    QVector<QString> selectedParams;

public slots:
    void StartLogging();
    void StopLogging();
    void OnClicked();

signals:
    void LogRequestTx(QVector<QString>logParams, bool start);

private:
    void RemoveParameter(QString param);
    void ConnectButtons();
    diagParams_t HashButtonName(QString name);

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

    QVBoxLayout *selectLeft;
    QVBoxLayout *selectRight;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
};

#endif // MAINMENU_H