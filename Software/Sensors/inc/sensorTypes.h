/**
 * @file sensorTypes.h
 * @author Joe Walker
 * @brief The class sensorTypes provides data types for the parking sensors.
 * @version 0.1
 * @date 2019-02-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SENSORTYPES_H
#define SENSORTYPES_H


/* @brief: Struct containing parking sensor pins */
typedef struct sensorPins_t {
    int sel[3];
    int echoPin;
    int triggerPin;
    int en;
} sensorPins_t;

#endif //SENSORTYPES_H