/*
 * robocart_driver.hpp
 *
 *  Created on: July 23, 2015
 *      Author: Daniella Niyonkuru
 */

#ifndef robocart_driver_HPP_
#define robocart_driver_HPP_

#include "sensors_port.hpp"
#include "motors_port.hpp"
#include "mbed.h"
#include "SeeedStudioShieldBot.h"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

DigitalIn hwbtn(PC_13);
SeeedStudioShieldBot bot(
    D8, D9, D11,              // Left motor pins
    D12, D10, D13,            // Right motor pins
    A0, A1, A2, A3, D4        // Sensors pins
);

bool startRight = true;
bool startLeft = true;
bool isStarted = false;

/* INPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool START_IN<TIME, MSG>::pDriver(Value &v) const noexcept {
	  if(!hwbtn){
		if(!isStarted){
			isStarted = true;
			v = 10;
		}
		else{
			isStarted = false;
			v = 11;
		}
		//printf("Button Pressed %d \n",v);
		return true;
	  }
	  else{
		return false;
	  }
}
template<class TIME, class MSG>
bool LIGHT_IN<TIME, MSG>::pDriver(Value &v) const noexcept {
    if(bot.getCentreSensor() == 0)
    	v = 1;
    else
    	v = 0;
	//printf("Light value = %d  \n",v);
	return true;
}


/* OUTPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool MOVER_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{ //motor left
	// This will be moved into the initHardware function
	if(startLeft){
		bot.enable_left_motor();
		startLeft = false;
	}
	if(v == 1){
	  bot.left_motor(0.08); //FWD the left motor
	  //printf("M1 - FWD \n");
	}
	else if(v == 2){
	  bot.left_motor(-0.08);//REV the left motor
	  //printf("M1 - BKWD \n");
	}
	else if(v == 0){
	  bot.left_motor(0); //Stop the left motor
	  //printf("M1 - STOP \n");
	}
	else{
	  //printf("Unchanged \n");
	}
	return true;

}

template<class TIME, class MSG>
bool MOVEL_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{ // motor right
	// This will be moved into the initHardware function
	if(startRight){
		bot.enable_right_motor();
		startRight = false;
	}

	if(v == 1){
	  bot.right_motor(0.08);
	  //printf("M2 - FWD \n");
	}
	else if(v == 2){
	  bot.right_motor(-0.08);
	  //printf("M2 - BKWD \n");
	}
	else if(v == 0){
	  bot.right_motor(0);
	  //printf("M2 - STOP \n");
	}
	else{
	  //printf("Unchanged \n");
	}
	return true;
}

#endif /* robocart_driver_HPP_ */
