/*
 * SensorController.hpp
 *
 *  Created on: Dec 9, 2018
 *      Author: Kyle and Ben
 */

#ifndef AlarmOutController_HPP_
#define AlarmOutController_HPP_

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
 * @brief RoomController PDEVS Model
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
class AlarmOutController1 : public atomic<TIME, MSG>
{
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    enum State {IDLE, SAFE, FIRE};

    enum Port {
    	fire_alarm_in,
		alarm_in,
		emerg_out1,
    };

    std::string portName[3];
    State _state;
    MSG _outputMessage;
	//Variables:
	const TIME infinity=boost::simulation::model<TIME>::infinity;
	bool isAlarming = false;
	bool isFire = false;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit AlarmOutController1(const std::string &n = "actrl1") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage(){
    	portName[fire_alarm_in] = "fire_alarm_in";
    	portName[alarm_in] = "alarm_out";
    	portName[emerg_out1] = "emerg_out1";
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
    	if(_state == IDLE) _outputMessage = MSG(portName[emerg_out1], 0);
    	if(_state == SAFE) _outputMessage = MSG(portName[emerg_out1], 1);
    	if(_state == FIRE) _outputMessage = MSG(portName[emerg_out1], 2);
		return std::vector<MSG>{_outputMessage};
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

    	if (msg.port == portName[fire_alarm_in]) {
			isFire = (msg.val == 1);
		} else if (msg.port == portName[alarm_in]) {
			isAlarming = (msg.val == 1);
		}

    	if(isFire) {
    		_state = FIRE;
    	} else {
    		if (isAlarming){
    			_state = SAFE;
    		} else {
    			_state = IDLE;
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

    void print()  noexcept {SWO_PrintString("actrl1");}

};


template<class TIME, class MSG>
class AlarmOutController2 : public atomic<TIME, MSG>
{
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    enum State {IDLE, SAFE, FIRE};

    enum Port {
    	heat_sensor_in,
		alarm_in,
		emerg_out2,
    };

    std::string portName[3];
    State _state;
    MSG _outputMessage;
	//Variables:
	const TIME infinity=boost::simulation::model<TIME>::infinity;
	bool isAlarming = false;
	bool isFire = false;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit AlarmOutController2(const std::string &n = "actrl2") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage(){
    	portName[heat_sensor_in] = "temperature_in";
    	portName[alarm_in] = "alarm_out";
    	portName[emerg_out2] = "emerg_out2";
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
    	if(_state == IDLE) _outputMessage = MSG(portName[emerg_out2], 0);
    	if(_state == SAFE) _outputMessage = MSG(portName[emerg_out2], 1);
    	if(_state == FIRE) _outputMessage = MSG(portName[emerg_out2], 2);
		return std::vector<MSG>{_outputMessage};
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

    	if (msg.port == portName[heat_sensor_in]) {
			isFire = (msg.val == 1);
		} else if (msg.port == portName[alarm_in]) {
			isAlarming = (msg.val == 1);
		}

    	if(isAlarming){
    		if (isFire){
    			_state = FIRE;
    		} else {
    			_state = SAFE;
    		}
    	} else {
    		_state = IDLE;
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

    void print()  noexcept {SWO_PrintString("actrl2");}

};
}
}
}
}


#endif /* AlarmOutController_HPP_ */
