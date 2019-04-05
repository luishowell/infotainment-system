#include "config.h"
#include "ultrasonic_sensor.h"
#include <iostream>

using namespace std;

//constructor
ultrasonic_sensor::ultrasonic_sensor(){
     //default the timeout to 2m
      this->setTimeout(2);
}


/*
    Function used to setup the pins on the pi that connect to the trigger and echo pins on the sensor
*/
bool ultrasonic_sensor::init(int trigger_pin, int echo_pin)
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
    
     //return true to indicate it is on a RPI
     return true;
#endif

     //if not on a RPI, return false
     return false;
 }

/*
    Function used to measure the distance from the sensor to the object
*/
bool ultrasonic_sensor::GetDistance(double *distance)
{

#ifdef RPI

     //pulse the trigger pin for 10us
     digitalWrite(this->m_trigger_pin, HIGH);
     delayMicroseconds(10);
     digitalWrite(this->m_trigger_pin, LOW);

     //timeout on both rising and falling edge of echo pin
     //timeoutLen = 12000;
     double time_left = timeoutLen;

     //time at which the while loop starts
     time_t while_start = micros();
     time_t time_taken;
     time_t while_end;

     //look for the rising edge of the echo pulse or timeout
     while((digitalRead(m_echo_pin) == LOW) && (time_left > 0))
     {
	  while_end = micros();
          time_taken = while_end - while_start;
          time_left = timeoutLen - time_taken;
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
     time_left = timeoutLen;
     while_start = micros();

     //look for the falling edge of the echo pulse or timeout
     while((digitalRead(m_echo_pin) == HIGH) && (time_left > 0))
     {
        while_end = micros();
        time_taken = while_end - while_start;
        time_left = timeoutLen - time_taken;
     }
     //record end time
     end_time = micros();
     

     //calculate the distance and return
     time_diff = difftime(end_time, start_time);
     *distance = this->calculateDistance(time_diff); //calculate the distance
     
     return true;
#endif
     return false; 
 }

/* Function to set the timeout length for a given maximum distance */
 bool ultrasonic_sensor::setTimeout(double maxDistance)
 {
      //check the given distance is valid
      if((maxDistance < 0)||(maxDistance > 5)){
          cout << "invalid maximum distance" << endl
          << "valid values are 0-5m" << endl;
          return false;
      }else{
          double d = maxDistance * 2; //double the distance for there and back
          this->timeoutLen = d/this->speedOfSound; //d=vt
          this->timeoutLen *= 1000000; //convert to microseconds
          this->timeoutLen = round(this->timeoutLen); //round it

          return true;
      }
 }

 /*Function that calculates the distance for a given pulse length*/
 double ultrasonic_sensor::calculateDistance(double pulseLen)
 {
      //check the pulse length is valid
      if(pulseLen < 0){
          return -999;
      }else{
          double returnVal = pulseLen * this->speedOfSound; //d=vt
          returnVal /= 2;                    //account for travel to and from
          returnVal /= 1000000;              //convert to metres
          return returnVal;
      }
 }