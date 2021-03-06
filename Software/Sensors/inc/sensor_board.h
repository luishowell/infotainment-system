/**
 * @file sensor_board.h
 * @author Joe Walker
 * @brief The class sensor_board provides methods for controlling the sensor board, containing the multiplexor and ultrasonic sensors.
 * @version 0.2
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SENSOR_BOARD_H
#define SENSOR_BOARD_H

#include "config.h"

#include <stdio.h>
#include <iostream>
#include <time.h>
#include "ultrasonic_sensor.h"
#include "multiplexor.h"
#include "types.h"


#ifdef RPI
#include <wiringPi.h>
#endif

/**
 * @brief Control of the ultrasonic sensors through the mux
 * 
 */

class sensor_board 
{
    public:

        /**
         * @brief sensor_board object constructor
         * 
         */
        sensor_board();

        /**
         * @brief Initialises the sensor board by initialising the multiplexor and ultrasonic sensor classes.
         * 
         * @param pins Struct of type sensorPins_t that contains all of the pin connections from the pi to the board.
         * @return Bool to indicate if init was successful
         */
        bool init(sensorPins_t pins);

        /**
         * @brief Reads the distance reported by a specified ultrasonic sensor.
         * 
         * @param sensor_num The number of the sensor to be read. 
         * @param *distance Pointer to the location the distance is to be stored.
         * @return bool Flag to report if the command has been successful.
         */
        bool GetDistance(unsigned int sensor_num, double *distance);


    private:

        //classes for the sensor and mux
        ultrasonic_sensor *sensor;
        multiplexor *mux;


};



#endif