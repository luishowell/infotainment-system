#include "ultrasonic_sensor.h"

//constructor
ultransoic_sensor::ultransoic_sensor(){}


/*
    Function used to setup the pins on the pi that connect to the trigger and echo pins on the sensor
*/
void ultransoic_sensor::init(int trigger_pin, int echo_pin)
 {

     //set the trigger pin as an output
     this->trigger_pin = trigger_pin;
     pinMode(trigger_pin, OUTPUT);

     //set the echo pin as an input
     pinMode(echo_pin, INPUT);
     this->echo_pin = echo_pin;

     //write a 0 to trigger pin
     digitalWrite (trigger_pin, LOW);
     

 }

/*
    Function used to measure the distance from the sensor to the object
*/
double ultransoic_sensor::get_distance()
 {

     //pulse the trigger pin for 10us
     digitalWrite(trigger_pin, HIGH);
     delayMicroseconds(10);
     digitalWrite(trigger_pin, LOW);

     //record start and end time of echo pulse
     while(digitalRead(echo_pin) == LOW);
     start_time = time(NULL);

     while(digitalRead(echo_pin) == HIGH);
     end_time = time(NULL);
     

     //calculate the distance and return
     time_diff = difftime(start_time, end_time);
     distance = (time_diff * 340)/2;                //d = v*t where v is the speed of sound at 340 m/s, div by two for there and back

     return distance; 


 }