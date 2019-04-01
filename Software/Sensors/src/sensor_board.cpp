#include "config.h"
#include "sensor_board.h"


//constructor
sensor_board::sensor_board(){}


//initialisation function
bool sensor_board::init(sensorPins_t pins)
{

    //initialise the sensor
    sensor = new ultrasonic_sensor();
    bool sensInit = sensor->init(pins.triggerPin, pins.echoPin);

    //initialise the mux
    mux = new multiplexor();
    bool muxInit = mux->init(pins.sel[0], pins.sel[1], pins.sel[2]);

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
    if(mux->set_mux(sensor_num) == false)
    {
        return false;
    }

#ifdef RPI
    delayMicroseconds(10); //wait for mux to be set properly
#endif

    //get the distance and return success
    return sensor->GetDistance(distance);
}