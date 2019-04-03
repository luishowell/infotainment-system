/**
 * @file LoggerWindow.cpp
 * @author Jamie Brown
 * @brief Implementation of LoggerWindow.
 * @version 0.1
 * @date 2019-02-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "LoggerWindow.h"
#include "Diagnostics.h"
#include "Hash.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>
#include <QFile>
#include <QtCore>
#include <iostream>
#include <string>
#include <vector>

LoggerWindow::LoggerWindow(std::vector<std::string> supportedPids, QWidget* parent)
{
    qDebug() << "LOGGER WINDOW: ";

    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    m_pids = supportedPids;
    uint16_t count;
    QVBoxLayout* selectLeft = new QVBoxLayout;
    QVBoxLayout* selectRight = new QVBoxLayout;
    QHBoxLayout* hLayout = new QHBoxLayout;
    QVBoxLayout* vLayout = new QVBoxLayout;

    /* smaller than screen size to superimpose on diagnostics window */
    setFixedSize(400, 200);

    m_startButton           = new QPushButton("Start Logging");
    m_startButton->setStyleSheet("QPushButton{color: green}");
    m_stopButton            = new QPushButton("Stop Logging");
    m_stopButton->setStyleSheet("QPushButton{color: red}");
    m_closeButton           = new QPushButton("Close");
    m_speedButton           = new QCheckBox("Speed");
    m_rpmButton             = new QCheckBox("RPM");
    m_fuelPressureButton    = new QCheckBox("Fuel Pressure");
    m_gearButton            = new QCheckBox("Current Gear");
    m_intakeAirTempButton   = new QCheckBox("Intake Air Temperature");
    m_engineRuntimeButton   = new QCheckBox("Engine Runtime");
    m_engineLoadButton      = new QCheckBox("Engine Load");
    m_throttleButton        = new QCheckBox("Throttle Position");

    /* open style for checkboxes */
    QFile styleFile("./MainApp/src/CustomCheckBox.qss");
    styleFile.open(QIODevice::ReadOnly);
    QTextStream textStream(&styleFile);
    QString styleSheet = textStream.readAll();
    qDebug() << "LOGGER WINDOW: " << styleSheet;
    styleFile.close();

    /* set green/amber/red style for checkbuttons */
    m_speedButton->setStyleSheet(styleSheet);
    m_rpmButton->setStyleSheet(styleSheet);
    m_fuelPressureButton->setStyleSheet(styleSheet);
    m_gearButton->setStyleSheet(styleSheet);
    m_intakeAirTempButton->setStyleSheet(styleSheet);
    m_engineRuntimeButton->setStyleSheet(styleSheet);
    m_engineLoadButton->setStyleSheet(styleSheet);
    m_throttleButton->setStyleSheet(styleSheet);

    m_startButton->setObjectName("Start");
    m_stopButton->setObjectName("Stop");
    m_speedButton->setObjectName("Speed");
    m_rpmButton->setObjectName("RPM");
    m_fuelPressureButton->setObjectName("Fuel Pressure");
    m_gearButton->setObjectName("Current Gear");
    m_intakeAirTempButton->setObjectName("Intake Air Temperature");
    m_engineRuntimeButton->setObjectName("Engine Runtime");
    m_engineLoadButton->setObjectName("Engine Load");
    m_throttleButton->setObjectName("Throttle Position");

    /* set disabled by default, will enable supported parameters later */
    m_engineLoadButton->setEnabled(false);
    m_rpmButton->setEnabled(false);
    m_speedButton->setEnabled(false);
    m_throttleButton->setEnabled(false);
    m_engineRuntimeButton->setEnabled(false);
    m_fuelPressureButton->setEnabled(false);
    m_intakeAirTempButton->setEnabled(false);
    m_gearButton->setEnabled(false);

    /* left layout buttons */
    selectLeft->addWidget(m_engineLoadButton);
    selectLeft->addWidget(m_rpmButton);
    selectLeft->addWidget(m_speedButton);
    selectLeft->addWidget(m_throttleButton);
    /* right layout buttons */
    selectRight->addWidget(m_engineRuntimeButton);
    selectRight->addWidget(m_fuelPressureButton);
    selectRight->addWidget(m_intakeAirTempButton);
    selectRight->addWidget(m_gearButton);

    for (count = 0; count < supportedPids.size(); count++)
    {
        switch(Hash::HashPID(supportedPids[count]))
        {
            /* left layout buttons */
            case ENGINE_LOAD :      m_engineLoadButton->setEnabled(true);
                                    break;
            case RPM :              m_rpmButton->setEnabled(true);
                                    break;
            case SPEED :            m_speedButton->setEnabled(true);
                                    break;
            case THROTTLE :         m_throttleButton->setEnabled(true);
                                    break;
            /* right layout buttons */
            case ENGINE_RUNTIME :   m_engineRuntimeButton->setEnabled(true);
                                    break;
            case FUEL_PRESSURE :    m_fuelPressureButton->setEnabled(true);
                                    break;
            case AIR_TEMP :         m_intakeAirTempButton->setEnabled(true);
                                    break;
            case GEAR :             m_gearButton->setEnabled(true);
                                    break;
            default :               break;
        }
    }
    hLayout->addLayout(selectLeft);
    hLayout->addLayout(selectRight);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_startButton);
    vLayout->addWidget(m_stopButton);
    vLayout->addWidget(m_closeButton);

    m_stopButton->hide();

    m_selectMsg = new QLabel(this);
    m_selectMsg->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    m_selectMsg->setText("Data Logger\nSelect parameters to log");
    vLayout->addWidget(m_selectMsg);

    if (supportedPids.size() == 0)
    {
        QLabel *label = new QLabel(this);
        label->setText("WARNING: vehicle does not support any parameters.\nEnsure your OBD2 adapter is connected correctly.");
        label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
        vLayout->addWidget(label);
        label->show();
        m_startButton->hide();
        m_selectMsg->hide();
        m_available = false;
    }
    else
    {
        m_selectMsg->show();
        m_available = true;
    }

    

    m_loggingMsg = new QLabel(this);
    m_msgTimer = new QTimer(this);
    connect(m_msgTimer, SIGNAL(timeout()), this, SLOT(UpdateLogMsg()));
    m_loggingMsg->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    vLayout->addWidget(m_loggingMsg);

    m_stoppedMsg = new QLabel(this);
    m_stoppedMsg->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    m_stoppedMsg->setText("FINISHED LOGGING\nResults written to DataLog");
    vLayout->addWidget(m_stoppedMsg);
    m_stoppedMsg->hide();

    this->setLayout(vLayout);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->move(200, 120);
    ConnectButtons();

    
}

void LoggerWindow::ShowMe()
{
    this->show();
    //m_selectMsg->show();
}

void LoggerWindow::ConnectButtons()
{
    connect(m_startButton, SIGNAL (clicked()), this, SLOT (StartLogging()));
    connect(m_stopButton, SIGNAL (clicked()), this, SLOT (StopLogging()));
    connect(m_closeButton, SIGNAL (clicked()), this, SLOT (CloseWindow()));

    connect(m_rpmButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_speedButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_intakeAirTempButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_throttleButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_gearButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_fuelPressureButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_engineRuntimeButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_engineLoadButton, SIGNAL (clicked()), this, SLOT (OnClicked()));

}

void LoggerWindow::CloseWindow()
{
    emit CloseRequest();
}

void LoggerWindow::StartLogging()
{
    /* emit start signal */
    qDebug() << "LOGGER: start button clicked";

    m_isLogging = true;
    m_selectMsg->hide();
    m_startButton->hide();
    m_stopButton->show();
    m_closeButton->setEnabled(false);
    m_loggingMsg->setText("Will now query OBD2 bus\n LOGGING");
    m_loggingMsg->show();
    m_msgCount = 0;
    m_msgTimer->start(1000);
    m_stoppedMsg->hide();
    DisableButtons();
    emit LogRequestTx(selectedParams, true);
}

void LoggerWindow::StopLogging()
{
    /* emit stop signal */
    qDebug() << "LOGGER: start button clicked";

    m_isLogging = false;
    m_stopButton->hide();
    m_startButton->show();
    m_closeButton->setEnabled(true);
    m_msgTimer->stop();
    m_loggingMsg->hide();
    m_stoppedMsg->show();
    EnableButtons();
    emit LogRequestTx(selectedParams, false);
}

void LoggerWindow::UpdateLogMsg()
{
    QString msg;
    msg = "Will now query OBD2 bus\n LOGGING";
    for (int count = 0; count < m_msgCount; count++) msg.append(".");
    if (m_msgCount == 3)
    { 
        m_msgCount = 0;
    }
    else
    {
        m_msgCount++;
    }
    m_loggingMsg->setText(msg);
}

void LoggerWindow::RemoveParameter(QString param)
{
    int count;
    for (count = 0; count < selectedParams.size(); count++)
    {
        if (selectedParams[count] == param) 
        { 
            selectedParams.erase(selectedParams.begin() + count);
        }
    }
}

void LoggerWindow::OnClicked()
{
    QObject *mySender = sender();
    QCheckBox *button = qobject_cast<QCheckBox*>(mySender);
    QString name = button->objectName();
    QString pid;

    switch(Hash::HashParameterName(name))
    {
        case RPM:               pid = "010C"; break;
        case SPEED:             pid = "010D"; break;                    
        case AIR_TEMP:          pid = "010F"; break;
        case THROTTLE:          pid = "0111"; break;
        case ENGINE_RUNTIME:    pid = "011F"; break;        
        case ENGINE_LOAD:       pid = "0104"; break;
        case GEAR:              pid = "01A4"; break;
        case FUEL_PRESSURE:     pid = "010A"; break;
    }

    if (button->isChecked())   
    {
        qDebug() << name << " selected";
        //std::cout << "PID: " << pid << endl; 
        selectedParams.push_back(pid);
        
        for (int i=0; i<selectedParams.size(); i++)
        {
            qDebug() << selectedParams[i]; 
        }
        //std::cout << endl;
        
    }
    else  
    { 
        qDebug() << name << " deselected"; 
        RemoveParameter(pid);
        /* 
        for (int i=0; i<selectedParams.size(); i++)
        {
            std::cout << selectedParams[i]; 
        }
        std::cout << endl;
        */
    }

}

void LoggerWindow::DisableButtons()
{
    m_speedButton->setEnabled(false);
    m_rpmButton->setEnabled(false);
    m_fuelPressureButton->setEnabled(false);
    m_gearButton->setEnabled(false);
    m_intakeAirTempButton->setEnabled(false);
    m_engineRuntimeButton->setEnabled(false);
    m_engineLoadButton->setEnabled(false);
    m_throttleButton->setEnabled(false);
    
}

void LoggerWindow::EnableButtons()
{
    for (int count = 0; count < m_pids.size(); count++)
    {
        switch(Hash::HashPID(m_pids[count]))
        {
            /* left layout buttons */
            case ENGINE_LOAD :      m_engineLoadButton->setEnabled(true);
                                    break;
            case RPM :              m_rpmButton->setEnabled(true);
                                    break;
            case SPEED :            m_speedButton->setEnabled(true);
                                    break;
            case THROTTLE :         m_throttleButton->setEnabled(true);
                                    break;
            /* right layout buttons */
            case ENGINE_RUNTIME :   m_engineRuntimeButton->setEnabled(true);
                                    break;
            case FUEL_PRESSURE :    m_fuelPressureButton->setEnabled(true);
                                    break;
            case AIR_TEMP :         m_intakeAirTempButton->setEnabled(true);
                                    break;
            case GEAR :             m_gearButton->setEnabled(true);
                                    break;
            default :               break;
        }
    }
}

void LoggerWindow::reset()
{
    EnableButtons();
    m_engineLoadButton->setChecked(false);
    m_rpmButton->setChecked(false);
    m_speedButton->setChecked(false);
    m_throttleButton->setChecked(false);
    m_engineRuntimeButton->setChecked(false);
    m_fuelPressureButton->setChecked(false);
    m_intakeAirTempButton->setChecked(false);
    m_gearButton->setChecked(false);
    m_stoppedMsg->hide();

    if (m_available) m_selectMsg->show();
}

bool LoggerWindow::isLogging() const
{
    return m_isLogging;
}





