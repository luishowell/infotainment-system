/**
 * @file types.h
 * @author Jamie Brown
 * @brief Contains all custom typedefs and structs used in the project
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

/**
 * @brief GUI view states
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
 * @brief diagnostics messages
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
 * @brief parameters that can be requested from the OBD2 thread
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
 * @brief 
 * 
 */
typedef enum {
    CHANNEL_A,
    CHANNEL_B
} obd2Channel_t;

/**
 * @brief parking sensor signals
 * 
 */
typedef struct sensorDist {
    bool connectionFault;
    double rearLeft;
    double rearRight;
    double rearCentre;
    double frontLeft;
    double frontRight;
    double frontCentre;
} sensorDist_t;


/**
 * @brief: Struct containing parking sensor pins 
 *
 */
typedef struct sensorPins_t {
    int sel[3];
    int echoPin;
    int triggerPin;
    int en;
} sensorPins_t;

/**
 * @brief: Accelerometer data type. 
 *
 */
typedef struct accValues_t {
    double xAxis;
    double yAxis;
    double zAxis;
} accValues_t;



#endif //TYPES_H