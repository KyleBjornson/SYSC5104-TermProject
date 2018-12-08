//
// main.cpp
// Copyright (c) 2015 Daniella Niyonkuru.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "eTime.h"
#include "eMessage.hpp"
#include "SensorController.hpp"
#include "MovementController.hpp"
#include "linerobot_driver.hpp"

// PDEVS core related include
#include <chrono>
#include <algorithm>
#include <boost/simulation.hpp>
#include <boost/rational.hpp>
#include <boost/lexical_cast.hpp>


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
	printf("Nucleo Board - Embedded CD-Boost \n\n");

	// Atomic models definition
	printf("Creating atomic models ... \n");
	auto sctrl = make_atomic_ptr<SensorController<Time, Message>>();
	auto mctrl = make_atomic_ptr<MovementController<Time, Message>>();

	//Coupled model definition
	printf("Creating Coupled models ... \n");
	shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{sctrl,mctrl}, {sctrl}, {{sctrl,mctrl}}, {mctrl}});

	//Top I/O port definition
	printf("Defining top I/O ports ... \n");
	// Input ports
	auto start = make_port_ptr<START_IN<Time, Message>>();
	auto light = make_port_ptr<LIGHT_IN<Time, Message>>();
    // Output ports
	auto motorleft = make_port_ptr<MOVEL_OUT<Time, Message>>();
	auto motorright = make_port_ptr<MOVER_OUT<Time, Message>>();

    // Execution parameter definition
	printf("Preparing runner \n");
	Time initial_time{Time::currentTime()};
	erunner<Time, Message> root{ControlUnit, {{start,sctrl},{light,sctrl}} , {{motorleft,mctrl},{motorright,mctrl}} };
	Time end_time{Time(0,30,0,0)};

	printf(("Starting simulation until time: seconds " + end_time.asString() + "\n").c_str());
	end_time = root.runUntil(end_time);


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
