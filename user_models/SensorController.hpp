/*
 * SensorController.hpp
 *
 *  Created on: May 7, 2015
 *      Author: Daniella
 */

#ifndef SensorController_HPP_
#define SensorController_HPP_

#include <boost/any.hpp>
#include <boost/simulation/pdevs/atomic.hpp>
#include "commonH.h"
#include "SWO.h"
#include "mbed.h"

namespace boost {
namespace simulation {
namespace pdevs {
namespace basic_models {
/**
 * @brief SensorController PDEVS Model
 *
 * SensorController PDEVS Model():
 * - X = {(start_in, {START, STOP}); (distance_in, {DISTANCE}); (light1_in, {BRIGHT, DARK}); (light2_in, {BRIGHT, DARK}); (light3_in, {BRIGHT, DARK}); (light4_in, {BRIGHT, DARK})}
 * - Y = {(sctrl_ls1start_out, {START, STOP}); (sctrl_ls2start_out, {START, STOP}); (sctrl_ls3start_out, {START, STOP}); (sctrl_ls4start_out, {START, STOP}); (proxystart_out, {START, STOP }); (stopdata_out, {STOP, NO_OBSTACLE}); (lsdata_out, {ON_TRACK, GO_LEFT, GO_RIGHT }}
 * - S = {“PREP_START,” “WAIT_DATA,” “FOUND_LIGHT,” “FOUND_ALL_LIGHT,” “FOUND_DISTANCE,” “PREP_IDLE,” “IDLE”}
 * - internal -> See DEVS Spec Doc
 * - external -> See DEVS Spec Doc
 * - out      -> See DEVS Spec Doc
 * - advance  -> See DEVS Spec Doc
*/
template<class TIME, class MSG>
class SensorController : public atomic<TIME, MSG>
{
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    enum State {IDLE, L1_off, L2_off, L1_on, L2_on};
    enum Port {sctrl_light_left_in, sctrl_light_right_in, sctrl_room1_out, sctrl_room2_out, sctrl_emerg1_out, sctrl_emerg2_out};
    std::string portName[6];
    State _state;
    MSG _outputMessage1,_outputMessage2, _outputMessage3, _outputMessage4;
	//Variables:

    bool toggle = true;

	TIME scTxTime = TIME(00,00,00,050);
	TIME scRxPrepTime = TIME(00,00,00,050);
	const TIME infinity=boost::simulation::model<TIME>::infinity;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit SensorController(const std::string &n = "sctrl") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage1(), _outputMessage2() {
    	portName[0] = "light_in_left"; portName[1] = "light_in_right"; portName[2] = "room1_out"; portName[3] = "room2_out"; portName[4] = "emergency1_out"; portName[5] = "emergency2_out";
    }

    /**
     * @brief internal function.
     */
    void internal() noexcept {

			_state = IDLE;
			_next = infinity;


    }
    /**
     * @brief advance function.
     * @return Time until next internal event.
     */
    TIME advance() const noexcept {
    	return _next;
    }
    /**
     * @brief out function.
     * @return MSG defined in construction.
     */
    std::vector<MSG> out() const noexcept {

    	if (_state == L1_on) {
    		_outputMessage1 = MSG(portName[sctrl_room1_out], 1); //Stop Light Sensor
    		_outputMessage2 = MSG(portName[sctrl_room2_out], 1); //Stop Movement Ctrl
    		return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	} else if (_state == L1_off) {
    		_outputMessage1 = MSG(portName[sctrl_room1_out], 0); //Stop Light Sensor
    		_outputMessage2 = MSG(portName[sctrl_room2_out], 0); //Stop Movement Ctrl
    		return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	} else if (_state == L2_on) {
    		_outputMessage1 = MSG(portName[sctrl_emerg1_out], 1); //Stop Light Sensor
    		_outputMessage2 = MSG(portName[sctrl_emerg2_out], 1); //Stop Movement Ctrl
    		return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	} else if (_state == L2_off) {
    		_outputMessage1 = MSG(portName[sctrl_emerg1_out], 0); //Stop Light Sensor
    		_outputMessage2 = MSG(portName[sctrl_emerg2_out], 0); //Stop Movement Ctrl
    		return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	}

		_outputMessage1 = MSG(portName[sctrl_room1_out], 0); //Stop Light Sensor
		_outputMessage2 = MSG(portName[sctrl_room2_out], 0); //Stop Movement Ctrl
		_outputMessage3 = MSG(portName[sctrl_emerg1_out], 0); //Stop Light Sensor
		_outputMessage4 = MSG(portName[sctrl_emerg2_out], 0); //Stop Movement Ctrl
    	return std::vector<MSG>{_outputMessage1, _outputMessage2, _outputMessage3, _outputMessage4};

    }
    /**
     * @brief external function
     * @param msg external input message.
     * @param t time the external input is received.
     */
    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

    	MSG msg = mb.back();

    	_next = Time::Zero;
    	_state = IDLE;

    	if (msg.port == portName[sctrl_light_left_in]) {
			if(msg.val == 1) {
				_state = L1_on;
				_next = Time::Zero;
			} else {
				_state = L1_off;
				_next = Time::Zero;
			}
		} else if (msg.port == portName[sctrl_light_right_in]) {
			if(msg.val == 1) {
				_state = L2_on;
				_next = Time::Zero;
			} else {
				_state = L2_off;
				_next = Time::Zero;
			}
		}
    }

    /**
     * @brief confluence function.
     * Execute the internal.
     *
     * @param msg
     * @param t time the external input is confluent with an internal transition.
     */
    void confluence(const std::vector<MSG>& mb, const TIME& t)  noexcept  {
    	internal();
		//external(mb,t);
    }

    void print()  noexcept {SWO_PrintString("sctrl");}

};

}
}
}
}


#endif /* SensorController_HPP_ */
