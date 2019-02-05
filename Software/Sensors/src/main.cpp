#include <stdio.h>
#include <iostream>
#include "sensorTypes.h"
#include "sensor_board.h"
#include "ultrasonic_sensor.h"
#include "multiplexor.h"
#include <wiringPi.h>

using namespace std;

int main(int argc, char** argv)
{

   //setup wiringpi
   wiringPiSetup();

   cout << "Sensor Test Starting" << endl;

   //create the sensor for just now as don't have mux
   //trigger on wiringPi 8, echo on 9
   //ultrasonic_sensor sens1;
   //sens1.init(8, 9);
   sensorPins_t pins;
	pins.en = 3;
	pins.echo_pin = 2;
	pins.trigger_pin = 0;
	pins.sel[0] = 12;
	pins.sel[1] = 13;
	pins.sel[2] = 14;

	sensor_board sens1;
	sens1.init(pins);


   string retry = "r";
   double distance;
   while(1){
      if(sens1.GetDistance(4, &distance) == true){
         cout << "Distance is: " << 100.0*distance << endl;
      }else{
         cout << "No echo pulse recorded" << endl;
      }

      //0.5 s delay to avoid overlaps
      delay(500);
   }

   return 0;




}