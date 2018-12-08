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
#include "ParallaxRobotShield.h"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

DigitalIn hwbtn(PC_13);
ParallaxRobotShield Parallax(D10, D11, PB_4, PA_8, 750, 303, 1.4, 1.55, 1.2, 1);

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
		printf("Button Pressed %d \n",v);
		return true;
	  }
	  else{
		return false;
	  }
}
template<class TIME, class MSG>
bool LIGHT_IN<TIME, MSG>::pDriver(Value &v) const noexcept {

	v = Parallax.lightSensor(D9);
	printf("Light value = %d  \n",v);
	return true;
}


/* OUTPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool MOVER_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{ //motor left
	  // This will be moved into the initHardware function
		if(startLeft){
			Parallax.enable_left_motor();
			startLeft = false;
		}
	  if(v == 1){
		  Parallax.left_servo(-20); //FWD the left motor
		  printf("M1 - FWD \n");
	  }
	  else if(v == 2){
		  Parallax.left_servo(20); //REV the left motor
		  printf("M1 - BKWD \n");
	  }
	  else if(v == 0){
		  Parallax.left_servo(0); //Stop the left motor
		  printf("M1 - STOP \n");
	  }
	  else{
		  Parallax.stopAll();
	  }
	  return true;

}

template<class TIME, class MSG>
bool MOVEL_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{ // motor right
	  // This will be moved into the initHardware function
		if(startRight){
			Parallax.enable_right_motor();
			startRight = false;
		}

	  if(v == 1){
		  Parallax.right_servo(-20);
		  printf("M2 - FWD \n");
	  }
	  else if(v == 2){
		  Parallax.right_servo(20);
		  printf("M2 - BKWD \n");
	  }
	  else if(v == 0){
		  Parallax.right_servo(0);
		  printf("M2 - STOP \n");
	  }
	  else{
		  Parallax.stopAll();
	  }
	  return true;
}

#endif /* robocart_driver_HPP_ */
