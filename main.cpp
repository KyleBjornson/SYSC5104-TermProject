//
// main.cpp
// Copyright (c) 2015 Daniella Niyonkuru.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "eTime.h"
#include "eMessage.hpp"
#include "linerobot_driver.hpp"

#include "mbed.h"

// PDEVS core related include
#include <chrono>
#include <algorithm>
#include <boost/simulation.hpp>
#include <boost/rational.hpp>
#include <boost/lexical_cast.hpp>
#include "user_models/RoomController.hpp"


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
	printf("Nucleo Board - Embedded CD-Boost \n\n");

	// Atomic models definition
	printf("Creating atomic models ... \n");
	auto rctrl = make_atomic_ptr<RoomController<Time, Message>>();
	//auto actrl = make_atomic_ptr<MovementController<Time, Message>>();

	//Coupled model definition
	printf("Creating Coupled models ... \n");
	//shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{sctrl,mctrl}, {sctrl}, {{sctrl,mctrl}}, {mctrl}});
	shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{rctrl}, {rctrl}, {{}}, {rctrl}});

	//Top I/O port definition
	printf("Defining top I/O ports ... \n");
	// Input ports
	//auto start = make_port_ptr<START_IN<Time, Message>>();
	auto light_left = make_port_ptr<LIGHT_IN_LEFT<Time, Message>>();
	//auto light_right = make_port_ptr<LIGHT_IN_RIGHT<Time, Message>>();
	auto ambient_light = make_port_ptr<AMBIENT_LIGHT_IN<Time, Message>>();
	//auto temperature = make_port_ptr<TEMPERATURE_IN<Time, Message>>();
    // Output ports
	auto room1 = make_port_ptr<ROOM1_OUT<Time, Message>>();
	//auto room2 = make_port_ptr<ROOM2_OUT<Time, Message>>();
	//auto emerg1 = make_port_ptr<EMERGENCY1_OUT<Time, Message>>();
	//auto emerg2 = make_port_ptr<EMERGENCY2_OUT<Time, Message>>();

    // Execution parameter definition
	printf("Preparing runner \n");
	Time initial_time{Time::currentTime()};
	//erunner<Time, Message> root{ControlUnit, {{light_left,sctrl},{light_right,sctrl},{ambient_light,sctrl},{temperature,sctrl}} , {{room1,sctrl},{room2,sctrl},{emerg1,sctrl},{emerg2,sctrl}} };
	erunner<Time, Message> root{ControlUnit, {{light_left,rctrl},{ambient_light,rctrl}} , {{room1,rctrl}} };
	Time end_time{Time(0,30,0,0)};

	printf(("Starting simulation until time: seconds " + end_time.asString() + "\n").c_str());
	end_time = root.runUntil(end_time);


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
