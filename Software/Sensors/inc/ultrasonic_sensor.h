/**
 * @file ultrasonic_sensor.h
 * @author Joe Walker
 * @brief The class ultrasonic_sensor provides methods for controlling the operation of an ultrasonic sensor from the raspberry pi.
 * @version 0.1
 * @date 2019-02-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "config.h"

#include <stdio.h>
#include <time.h>

#ifdef RPI
#include <wiringPi.h>
#endif

class ultrasonic_sensor
{
    public:

        /**
         * @brief ultrasonic_sensor object constructor
         */
        ultrasonic_sensor();

        /**
         * @brief Initialises the ultrasonic sensor
         * 
         * @param trigger_pin The wiringPi pin number of the pin connected to the trigger of the ultransonic sensor.
         * @param echo_pin The wiringPi pin number of the pin connected to the trigger of the ultrasonic sensor.
         */
        void init(int trigger_pin, int echo_pin);


        /**
         * @brief Reads the distance reported by an ultrasonic sensor up to 2m.
         * 
         * @param *distance Pointer to the location that the distance should be recorded. The value is recorded in metres.
         * @return bool Flag that reports if the command has been successful or not.
         */
        bool GetDistance(double *distance);

    private:

        //gpio pin connections
        int m_trigger_pin;             //pin that connects to the trigger of the sensor
        int m_echo_pin;                //pin that connects to the echo of the sensor

        //start and end time variables
        time_t start_time;
        time_t end_time;

        //calculated variables
        double time_diff;
        double m_distance;


};




#endif