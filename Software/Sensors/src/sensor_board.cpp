/**
 * @file sensor_board.cpp
 * @author Joe Walker
 * @brief Implementation of sensor_board class
 * @version 0.2
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "config.h"
#include "sensor_board.h"


//constructor
sensor_board::sensor_board(){
    this->sensor = new ultrasonic_sensor();
    this->mux = new multiplexor();    
}


//initialisation function
bool sensor_board::init(sensorPins_t pins)
{

    //initialise the sensor
    bool sensInit = this->sensor->init(pins.triggerPin, pins.echoPin);

    //initialise the mux
    bool muxInit = this->mux->init(pins.sel[0], pins.sel[1], pins.sel[2]);

#ifdef RPI  
    //control enable pin
    pinMode(pins.en, OUTPUT);
    digitalWrite(pins.en, LOW);
#else
    return false;
#endif

    //if either of the inits have failed report the failure
    if((sensInit == false) || (muxInit == false))
    {
        return false;
    }else{
        return true;
    }
}

//main get distance function
bool sensor_board::GetDistance(unsigned int sensor_num, double *distance)
{

    //set the mux to the correct value and check response
    if(this->mux->set_mux(sensor_num) == false)
    {
        return false;
    }

#ifdef RPI
	//std::cout << "MUX DELAY" << std::endl;
    delayMicroseconds(70000); //wait for mux to be set properly
#endif

    //get the distance and return success
    return this->sensor->GetDistance(distance);
}