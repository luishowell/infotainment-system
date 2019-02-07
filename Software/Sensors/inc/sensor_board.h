#ifndef SENSOR_BOARD_H
#define SENSOR_BOARD_H

#include <stdio.h>
#include <wiringPi.h>
#include "ultrasonic_sensor.h"
#include "multiplexor.h"
#include "sensorTypes.h"

class sensor_board 
{
    public:

        //constructor
        sensor_board();

        //initialisation function
        void init(sensorPins_t pins);

        //get distance function
        bool GetDistance(unsigned int sensor_num, double *distance);


    private:

        //classes for the sensor and mux
        ultrasonic_sensor *sensor;
        multiplexor *mux;


};



#endif