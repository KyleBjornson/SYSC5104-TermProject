//
// main.cpp
//  Created on: Dec 9, 2018
//       Author: Kyle and Ben

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "eTime.h"
#include "eMessage.hpp"
#include "mbed.h"

// PDEVS core related include
#include <chrono>
#include <algorithm>
#include <boost/simulation.hpp>
#include <boost/rational.hpp>
#include <boost/lexical_cast.hpp>

#include "user_drivers/drivers.hpp"
#include "user_models/RoomController.hpp"
#include "user_models/AlarmMonitor.hpp"
#include "user_models/AlarmOutController.hpp"


using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;
using namespace std;
// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	initPins();
	//lightTest();while(1);

	printf("Nucleo Board - Embedded CD-Boost \n\n");

	// Atomic models definition
	printf("Creating atomic models ... \n");
	auto rctrl1 = make_atomic_ptr<RoomController1<Time, Message>>();
	auto rctrl2 = make_atomic_ptr<RoomController2<Time, Message>>();
	//auto amon = make_atomic_ptr<AlarmMonitor<Time, Message>>();
	auto actrl1 = make_atomic_ptr<AlarmOutController1<Time, Message>>();
	auto actrl2 = make_atomic_ptr<AlarmOutController2<Time, Message>>();


	//Coupled model definition
	printf("Creating Coupled models ... \n");
	//shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{sctrl,mctrl}, {sctrl}, {{sctrl,mctrl}}, {mctrl}});
	shared_ptr<flattened_coupled<Time, Message>> ControlUnit(new flattened_coupled<Time, Message> {
		{rctrl1, rctrl2, actrl1, actrl2},
		{rctrl1, rctrl2, actrl1, actrl2},
		//{rctrl1, rctrl2, amon, actrl1, actrl2},
		//{rctrl1, rctrl2, amon, actrl1, actrl2},
		{
		//	{amon,actrl1},
		//	{amon,actrl2}
		},
		{rctrl1, rctrl2, actrl1, actrl2}
	});

	//Top I/O port definition
	printf("Defining top I/O ports ... \n");
	// Input ports
	auto light_left = make_port_ptr<LIGHT_IN_LEFT<Time, Message>>();
	auto light_right = make_port_ptr<LIGHT_IN_RIGHT<Time, Message>>();
	auto ambient_light = make_port_ptr<AMBIENT_LIGHT_IN<Time, Message>>();
	auto fire_alarm = make_port_ptr<FIRE_ALARM<Time, Message>>();
	auto temperature = make_port_ptr<TEMPERATURE_IN<Time, Message>>();
    // Output ports
	auto room1 = make_port_ptr<ROOM1_OUT<Time, Message>>();
	auto room2 = make_port_ptr<ROOM2_OUT<Time, Message>>();
	auto emerg1 = make_port_ptr<EMERGENCY1_OUT<Time, Message>>();
	auto emerg2 = make_port_ptr<EMERGENCY2_OUT<Time, Message>>();

    // Execution parameter definition
	printf("Preparing runner \n");
	Time initial_time{Time::currentTime()};
	erunner<Time, Message> root {
		ControlUnit,
		{//External Input Coupling
			{light_left,rctrl1},
			{ambient_light,rctrl1},
			{light_right,rctrl2},
			{ambient_light,rctrl2},
			{fire_alarm,actrl2},
			{fire_alarm,actrl1},
			{temperature,actrl1},
			{temperature,actrl2},
		},
		{//External Output Coupling
			{room1,rctrl1},
			{room2,rctrl2},
			{emerg1,actrl1},
			{emerg2,actrl2},

		}
	};
	Time end_time{Time(0,30,0,0)};

	printf(("Starting simulation until time: seconds " + end_time.asString() + "\n").c_str());
	end_time = root.runUntil(end_time);


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
