/*
 * robocart_driver.hpp
 *
 *  Created on: July 23, 2015
 *      Author: Daniella Niyonkuru
 */

#ifndef robocart_driver_HPP_
#define robocart_driver_HPP_

#include "actuators_port.hpp"
#include "sensors_port.hpp"
#include "mbed.h"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

#define AMBIENT_LIGHT_THRESHOLD 0.5f
#define TEMPERATURE_THRESHOLD 500

//DigitalIn hwbtn(PC_13);

DigitalIn leftSensor(A0);
DigitalIn rightSensor(A3);

AnalogIn ambientLightSensor(A4);
AnalogIn temperatureSensor(A2);

DigitalOut room1Led1(D6);
DigitalOut room1Led2(D7);
DigitalOut room2Led1(D8);
DigitalOut room2Led2(D9);

DigitalOut emerg1Red(D2);
DigitalOut emerg1Green(D3);
DigitalOut emerg2Red(D4);
DigitalOut emerg2Green(D5);


/* INPUT PORTS DRIVERS */
//template<class TIME, class MSG>
//bool START_IN<TIME, MSG>::pDriver(Value &v) const noexcept {
//	  if(!hwbtn){
//		if(!isStarted){
//			isStarted = true;
//			v = 10;
//		}
//		else{
//			isStarted = false;
//			v = 11;
//		}
//		//printf("Button Pressed %d \n",v);
//		return true;
//	  }
//	  else{
//		return false;
//	  }
//}

void initPins(void) {
	room1Led1 = 0;
	room1Led2 = 0;
	room2Led1 = 0;
	room2Led2 = 0;

	emerg1Red = 0;
	emerg1Green = 0;
	emerg2Red = 0;
	emerg2Green = 0;
}


template<class TIME, class MSG>
bool LIGHT_IN_LEFT<TIME, MSG>::pDriver(Value &v) const noexcept {
    if(leftSensor == 0)
    	v = 1;
    else
    	v = 0;
	//printf("Light value = %d  \n",v);
	return true;
}

template<class TIME, class MSG>
bool LIGHT_IN_RIGHT<TIME, MSG>::pDriver(Value &v) const noexcept {
    if(rightSensor == 0)
    	v = 1;
    else
    	v = 0;
	//printf("Light value = %d  \n",v);
	return true;
}

template<class TIME, class MSG>
bool AMBIENT_LIGHT_IN<TIME, MSG>::pDriver(Value &v) const noexcept {
    if(ambientLightSensor.read() > AMBIENT_LIGHT_THRESHOLD)
    	v = 1;
    else
    	v = 0;
	//printf("Light value = %d  \n",v);
	return true;
}

template<class TIME, class MSG>
bool TEMPERATURE_IN<TIME, MSG>::pDriver(Value &v) const noexcept {
    if(temperatureSensor > TEMPERATURE_THRESHOLD)
    	v = 1;
    else
    	v = 0;
	//printf("Light value = %d  \n",v);
	return true;
}


/* OUTPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool ROOM1_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{ //motor left

	if (v == 0) {
		room1Led1 = 0;
		room1Led2 = 0;
	} else if (v == 1) {
		room1Led1 = 0;
		room1Led2 = 1;
	} else {
		room1Led1 = 1;
		room1Led2 = 1;
	}

	//if(v == 1){
	//  bot.left_motor(0.08); //FWD the left motor
	  //printf("M1 - FWD \n");
	//}

	return true;
}

template<class TIME, class MSG>
bool ROOM2_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{

	if (v == 0) {
		room2Led1 = 0;
		room2Led2 = 0;
	} else if (v == 1) {
		room2Led1 = 0;
		room2Led2 = 1;
	} else {
		room2Led1 = 1;
		room2Led2 = 1;
	}

	return true;
}

template<class TIME, class MSG>
bool EMERGENCY1_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{
	if (v == 1) {
		emerg1Red = 1;
		emerg1Green = 1;
	} else {
		emerg1Red = 0;
		emerg1Green = 0;
	}

	return true;
}

template<class TIME, class MSG>
bool EMERGENCY2_OUT<TIME, MSG>::pDriver(Value& v) const noexcept{
	if (v == 1) {
		emerg2Red = 1;
		emerg2Green = 1;
	} else {
		emerg2Red = 0;
		emerg2Green = 0;
	}

	return true;
}

#endif /* robocart_driver_HPP_ */
