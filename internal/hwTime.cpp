/*
 * hwtime.cpp
 *
 *  Created on: May 11, 2015
 *      Author: Daniella(Version 2)
 */
#include "hwTime.h"
#include "mbed.h"


// Global variables
int hrs;
unsigned int hrsAsMic = 0xD693A400 - 0x1; // 1 hour as microseconds = 3,600,000,000 - 1 for 0 based counting
unsigned int us = 0;
unsigned int isTimeStopped = 0;
RTIME nowT;

void clockInit(){
	hrs = 0;
	isTimeStopped = 0;
	nowT = 0;
}
// increments the hour counter
void inc(void){
	hrs++;
}

// returns the current execution time
RTIME rt_timer_read(void){
	return us_ticker_read();
}

int interrupted = 0;
int wasInterrupted = 0;
// sleeps
void hw_sleep(void){
	// Go to sleep and wait for interrupt - Power saving mode
	//__WFE();//__WFI();
	while(rt_timer_read() < 3600000000){
		if(isInterrupted()){
			interrupted = 0;
			return;
		}
	}
}


// sleeps for a specified period of time
int sleepFor(RTIME wake){
	RTIME now;

	now = rt_timer_read();
	while(rt_timer_read() - now < wake){
		if(isInterrupted()){
			interrupted = 0;
			return 1;
		}
	}
	return 0;
}

// sleeps until a certain time
int sleepUntil(RTIME wakeTime){

	while(rt_timer_read() < wakeTime){
		if(isInterrupted()){
			interrupted = 0;
			return 1;
		}
	}
	return 0;
}

// checks if the sleep has been interrupted
int isInterrupted(void){
	return interrupted;
}

// sets the sleep to interrupted
void setInterrupted(void){
	interrupted = 1;
	wasInterrupted = 1;
}

void clearInterrupted(void){
	interrupted = 0;
}

// For debug purposes only //
void RTTimerWrite(RTIME t){
	TIM5->CNT = t;
}
RTIME RTTimerRead(void){
	return (RTIME)(TIM5->CNT);
}

void stopTimer(void){
	isTimeStopped = 1;
	nowT = RTTimerRead();
}

void resumeTimer(void){
	RTTimerWrite(nowT);
	isTimeStopped = 0;
}
