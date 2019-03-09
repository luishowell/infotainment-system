/**
 * @file sensor_board.h
 * @author Joe Walker
 * @brief The class sensor_board provides methods for controlling the sensor board, containing the multiplexor and ultrasonic sensors.
 * @version 0.1
 * @date 2019-02-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SENSOR_BOARD_H
#define SENSOR_BOARD_H

#include "config.h"

#include <stdio.h>
#include "ultrasonic_sensor.h"
#include "multiplexor.h"
#include "sensorTypes.h"

#ifdef RPI
#include <wiringPi.h>
#endif

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
         */
        void init(sensorPins_t pins);

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