/**
 * @file MMA8652FCR1.h
 * @author Joe Walker
 * @brief The class MMA8652FCR1.h provides methods for controlling the operation of the accelerometer of the same name.
 * @version 0.1
 * @date 2019-02-25
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef MMA8652FCR1_H
#define MMA8652FCR1_H

#include "config.h"
#include "sensorTypes.h"

#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <cmath>
#include <string.h>

#ifdef RPI
#include <wiringPi.h>
#include <wiringPiI2C.h>
#endif

class MMA8652FCR1
{

    public:

        /**
         * @brief MMA8652FCR1 object constructor
         */
        MMA8652FCR1();
        
        /**
         * @brief Initialises the accelerometer and configures registers.
         *
         * @param devID The device ID of the accelerometer.
         * @param intPin1 The wiringPi pin number of the pin connected to interrupt 1.
         * @param intPin2 The wiringPi pin number of the pin connected to interrupt 2.
         * @return Bool that reports if the setup has been successful.
         */
        bool init(int devID, int intPin1, int intPin2);
        
        /**
         * @brief Gets the acceleration value from each of the three axis.
         *
         * @param data Pointer to a accValues_t struct that contains the x, y and z accelerations.
         */
        void getData(accValues_t *data);
        
    private:
    
        //2's complement data conversion functions
        double twosComp(uint8_t MSB);
        double twosComp(uint8_t MSB, uint8_t LSB);
    
        //interrupt pin connections
        int m_intPin1;
        int m_intPin2;
        
        //accelerometer offset values
        //double xOffset;
        //double yOffset;
        //double zOffset;
        
        //devid of the sensor
        int m_devID;
        
        //i2c port
        int fd;

};

#endif