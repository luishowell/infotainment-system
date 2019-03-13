#include "config.h"
#include "ultrasonic_sensor.h"
#include <iostream>

using namespace std;

//constructor
ultrasonic_sensor::ultrasonic_sensor(){}


/*
    Function used to setup the pins on the pi that connect to the trigger and echo pins on the sensor
*/
void ultrasonic_sensor::init(int trigger_pin, int echo_pin)
 {
#ifdef RPI

     //set the trigger pin as an output
     this->m_trigger_pin = trigger_pin;
     pinMode(trigger_pin, OUTPUT);

     //set the echo pin as an input
     pinMode(echo_pin, INPUT);
     this->m_echo_pin = echo_pin;

     //write a 0 to trigger pin
     digitalWrite (trigger_pin, LOW);
    
#endif
 }

/*
    Function used to measure the distance from the sensor to the object
*/
bool ultrasonic_sensor::GetDistance(double *distance)
{
#ifdef RPI

     //pulse the trigger pin for 10us
     digitalWrite(m_trigger_pin, HIGH);
     delayMicroseconds(10);
     digitalWrite(m_trigger_pin, LOW);

     //timeout of 12 ms on both rising and falling edge of echo pin
     double timeout_len = 12000;
     double time_left = timeout_len;

     //time at which the while loop starts
     time_t while_start = micros();
     time_t time_taken;
     time_t while_end;

     //look for the rising edge of the echo pulse or timeout
     while((digitalRead(m_echo_pin) == LOW) && (time_left > 0))
     {
	    while_end = micros();
        time_taken = while_end - while_start;
        time_left = timeout_len - time_taken;
     }


     //if it timed out, return error response, else record time
     if(time_left < 0)
     {
	cout << "return false" << endl;
        return false;
     }else{
	cout << "echo returned" << endl;
        start_time = micros();
     }



     //reset timeout values
     time_left = timeout_len;
     while_start = micros();

     //look for the falling edge of the echo pulse or timeout
     while((digitalRead(m_echo_pin) == HIGH) && (time_left > 0))
     {
        while_end = micros();
        time_taken = while_end - while_start;
        time_left = timeout_len - time_taken;
     }
     //record end time
     end_time = micros();
     

     //calculate the distance and return
     time_diff = difftime(end_time, start_time);
     *distance = (time_diff * 340)/2000000;                //d = v*t where v is the speed of sound at 340 m/s, div by two for there and back
     
#endif
     return true; 
 }