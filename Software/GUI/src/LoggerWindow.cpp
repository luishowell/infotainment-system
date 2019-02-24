/**
 * @file LoggerWindow.cpp
 * @author Jamie Brown
 * @brief 
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
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Construct a new Logger Window:: Logger Window object
 * 
 * @param parent 
 * @param supportedPids 
 */
LoggerWindow::LoggerWindow(QVector<QString> supportedPids)
{
    uint16_t count;
    QVBoxLayout* selectLeft = new QVBoxLayout;
    QVBoxLayout* selectRight = new QVBoxLayout;
    QHBoxLayout* hLayout = new QHBoxLayout;
    QVBoxLayout* vLayout = new QVBoxLayout;

    /* smaller than screen size to superimpose on diagnostics window */
    setFixedSize(400, 200);

    m_startButton           = new QPushButton("Start Logging");
    m_stopButton            = new QPushButton("Stop Logging");
    m_speedButton           = new QCheckBox("Speed");
    m_rpmButton             = new QCheckBox("RPM");
    m_fuelPressureButton    = new QCheckBox("Fuel Pressure");
    m_gearButton            = new QCheckBox("Current Gear");
    m_intakeAirTempButton   = new QCheckBox("Intake Air Temperature");
    m_engineRuntimeButton   = new QCheckBox("Engine Runtime");
    m_engineLoadButton      = new QCheckBox("Engine Load");
    m_throttleButton        = new QCheckBox("Throttle Position");

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

    for (count = 0; count < supportedPids.size(); count++)
    {
        switch(Hash::HashPID(supportedPids[count]))
        {
            /* left layout buttons */
            case ENGINE_LOAD :      selectLeft->addWidget(m_engineLoadButton);
                                    break;
            case RPM :              selectLeft->addWidget(m_rpmButton);
                                    break;
            case SPEED :            selectLeft->addWidget(m_speedButton);
                                    break;
            case THROTTLE :         selectLeft->addWidget(m_throttleButton);
                                    break;
            /* right layout buttons */
            case ENGINE_RUNTIME :   selectRight->addWidget(m_engineRuntimeButton);
                                    break;
            case FUEL_PRESSURE :    selectRight->addWidget(m_fuelPressureButton);
                                    break;
            case AIR_TEMP :         selectRight->addWidget(m_intakeAirTempButton);
                                    break;
            case GEAR :             selectRight->addWidget(m_gearButton);
                                    break;
            default :               break;
        }
    }
    hLayout->addLayout(selectLeft);
    hLayout->addLayout(selectRight);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_startButton);
    

    this->setLayout(vLayout);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    this->move(200, 120);
    ConnectButtons();
}

/**
 * @brief 
 * 
 */
void LoggerWindow::ConnectButtons()
{
    connect(m_startButton, SIGNAL (clicked()), this, SLOT (StartLogging()));
    connect(m_stopButton, SIGNAL (clicked()), this, SLOT (StopLogging()));

    connect(m_rpmButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_speedButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_intakeAirTempButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_throttleButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_gearButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_fuelPressureButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_engineRuntimeButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    connect(m_engineLoadButton, SIGNAL (clicked()), this, SLOT (OnClicked()));
    /*
   connect(m_rpmButton, SIGNAL (clicked()), this, SLOT (RpmSelect()));
   connect(m_speedButton, SIGNAL (clicked()), this, SLOT (SpeedSelect()));
   connect(m_intakeAirTempButton, SIGNAL (clicked()), this, SLOT (AirTempSelect()));
   connect(m_throttleButton, SIGNAL (clicked()), this, SLOT (ThrottleSelect()));
   connect(m_gearButton, SIGNAL (clicked()), this, SLOT (GearSelect()));
   connect(m_fuelPressureButton, SIGNAL (clicked()), this, SLOT (FuelPressureSelect()));
   connect(m_engineRuntimeButton, SIGNAL (clicked()), this, SLOT (EngineRuntimeSelect()));
   connect(m_engineLoadButton, SIGNAL (clicked()), this, SLOT (EngineLoadSelect()));
   */
}

/**
 * @brief 
 * 
 */
void LoggerWindow::StartLogging()
{
    /* emit start signal */
    qDebug() << "LOGGER: start button clicked";
    emit LogRequestTx(selectedParams);
}

/**
 * @brief 
 * 
 */
void LoggerWindow::StopLogging()
{

    /* emit stop signal */
}

/**
 * @brief 
 * 
 * @param param 
 */
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

/**
 * @brief 
 * 
 */
void LoggerWindow::OnClicked()
{
    QObject *mySender = sender();
    QCheckBox *button = qobject_cast<QCheckBox*>(mySender);
    QString name = button->objectName();
    QString pid;

    switch(Hash::HashParameterName(name))
    {
        case RPM:               pid = "0C"; break;
        case SPEED:             pid = "0D"; break;                    
        case AIR_TEMP:          pid = "0F"; break;
        case THROTTLE:          pid = "11"; break;
        case ENGINE_RUNTIME:    pid = "1F"; break;        
        case ENGINE_LOAD:       pid = "04"; break;
        case GEAR:              pid = "A4"; break;
        case FUEL_PRESSURE:     pid = "0A"; break;
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








