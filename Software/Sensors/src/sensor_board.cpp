#include "config.h"
#include "sensor_board.h"


//constructor
sensor_board::sensor_board(){}


//initialisation function
void sensor_board::init(sensorPins_t pins)
{

    //initialise the sensor
    sensor = new ultrasonic_sensor();
    sensor->init(pins.triggerPin, pins.echoPin);

    //initialise the mux
    mux = new multiplexor();
    mux->init(pins.sel[0], pins.sel[1], pins.sel[2]);
#ifdef RPI  
    //control enable pin
    pinMode(pins.en, OUTPUT);
    digitalWrite(pins.en, LOW);
#endif

}

//main get distance function
bool sensor_board::GetDistance(unsigned int sensor_num, double *distance)
{
#ifdef RPI

    //set the mux to the correct value and check response
    if(mux->set_mux(sensor_num) == false)
    {
        return false;
    }

    delayMicroseconds(10); //wait for mux to be set properly

#endif
    //get the distance and return success
    return sensor->GetDistance(distance);

}