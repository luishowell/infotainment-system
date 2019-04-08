/**
 * @file types.h
 * @author Jamie Brown
 * @brief Contains all custom typedefs and structs used in the project.
 * @version 0.1
 * @date 2019-02-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TYPES_H
#define TYPES_H

//#include <QGroupBox>
//#include <QMetaType>
#include <string>
#include <QString>
#include <QImage>
#include <QPointer>

/**
 * @brief Enumeration of GUI view states.
 * 
 */
typedef enum{
    MAIN_MENU,
    DIAGNOSTICS,
    ERROR_CODES,
    MEDIA,
    PARKING
} state_t;

/**
 * @brief Structure containing requested OBD2 parameters for a given channel.
 * 
 */
typedef struct diagMsg {
    bool connectionFault;
    int channelA;
    int channelB;
    std::string requestA;
    std::string requestB;
} diagMsg_t;

/**
 * @brief Structure containing audio meta-data for a given mp3 file.
 * 
 */
typedef struct audioMetaData
{
    QString title;
    QString artist;
    QString album;
    QString genre;
    QString year;
    QImage albumArt;
    int duration;
    const char* filePath;
} audioMetaData_t;

/**
 * @brief Enumeration of parameters that can be requested from the CANWorker/CANThread.
 * 
 */
typedef enum {
    SPEED,
    RPM,
    AIR_TEMP, 
    THROTTLE,
    GEAR,
    FUEL_PRESSURE,
    ENGINE_LOAD,
    ENGINE_RUNTIME
} diagParams_t;
//Q_DECLARE_METATYPE(diagParams_t)

/**
 * @brief Enumeration of OBD2 chanels.
 * 
 */
typedef enum {
    CHANNEL_A,
    CHANNEL_B
} obd2Channel_t;

/**
 * @brief Structure of parking sensor signals for each sensor.
 * 
 */
typedef struct sensorDist {
    bool rearLeftConnectionFault;
    bool rearRightConnectionFault;
    bool rearCentreConnectionFault;
    bool frontLeftConnectionFault;
    bool frontRightConnectionFault;
    bool frontCentreConnectionFault;
    double rearLeft;
    double rearRight;
    double rearCentre;
    double frontLeft;
    double frontRight;
    double frontCentre;
} sensorDist_t;


/**
 * @brief: Structure of parking sensor pins .
 *
 */
typedef struct sensorPins_t {
    int sel[3];
    int echoPin;
    int triggerPin;
    int en;
} sensorPins_t;

/**
 * @brief: Structure of accelerometer data types. 
 *
 */
typedef struct accValues_t {
    double xAxis;
    double yAxis;
    double zAxis;
} accValues_t;



#endif //TYPES_H