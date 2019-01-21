#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>


class ultransoic_sensor
{
    public:

        //constructor
        ultransoic_sensor();

        //function to initialise the sensor
        void init(int trigger_pin, int echo_pin);


        //function to get the distance of the sensor to an object
        double get_distance();

    private:

        //gpio pin connections
        int trigger_pin             //pin that connects to the trigger of the sensor
        int echo_pin                //pin that connects to the echo of the sensor

        //start and end time variables
        time_t start_time;
        time_t end_time;

        //calculated variables
        double time_diff;
        double distance;


};




#endif