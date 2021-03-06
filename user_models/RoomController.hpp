/*
 * RoomController.hpp
 *
 *  Created on: Dec 9, 2018
 *      Author: Kyle and Ben
 */

#ifndef RoomController_HPP_
#define RoomController_HPP_

#include <boost/any.hpp>
#include <boost/simulation/pdevs/atomic.hpp>
#include "SWO.h"
#include "mbed.h"

namespace boost {
namespace simulation {
namespace pdevs {
namespace basic_models {
/**
 * @brief RoomController PDEVS Model
 * See DEVS Spec Doc
*/
template<class TIME, class MSG>
class RoomController1 : public atomic<TIME, MSG>
{
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    enum State {IDLE, HALF, FULL};

    enum Port {
    	rctrl_light_in,
		rctrl_ambient_light_in,
//		rctrl_emerg_in,
		rctrl_room_out,
    };

    std::string portName[4];
    State _state;
    MSG _outputMessage;
	//Variables:
	const TIME infinity=boost::simulation::model<TIME>::infinity;
	bool isOccupied = false;
	bool isBright = false;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit RoomController1(const std::string &n = "rctrl1") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage(){
    	portName[rctrl_light_in] = "light_in1";
    	portName[rctrl_ambient_light_in] = "ambient_light_in";
    	//portName[rctrl_emerg_in] = "emergency_in1";
    	portName[rctrl_room_out] = "room_out1";
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
    	if(_state == IDLE) _outputMessage = MSG(portName[rctrl_room_out], 0);
    	if(_state == HALF) _outputMessage = MSG(portName[rctrl_room_out], 1);
    	if(_state == FULL) _outputMessage = MSG(portName[rctrl_room_out], 2);
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

    	if (msg.port == portName[rctrl_light_in]) {//sctrl_light_left_in]) {
			isOccupied = (msg.val == 1);
		} else if (msg.port == portName[rctrl_ambient_light_in]) {
			isBright = (msg.val == 1);
		}

    	if(isOccupied){
    		if (isBright){
    			_state = HALF;
    		} else {
    			_state = FULL;
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
    }

    void print()  noexcept {SWO_PrintString("rctrl1");}

};

/* Second RoomController.
 * -> Our intention was to instantiate the first AlarmOutController twice in main.cpp
 *    but we were unable to do so.
 */

template<class TIME, class MSG>
class RoomController2 : public atomic<TIME, MSG>
{
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    enum State {IDLE, HALF, FULL};

    enum Port {
    	rctrl_light_in,
		rctrl_ambient_light_in,
//		rctrl_emerg_in,
		rctrl_room_out,
    };

    std::string portName[4];
    State _state;
    MSG _outputMessage;
	//Variables:
	const TIME infinity=boost::simulation::model<TIME>::infinity;
	bool isOccupied = false;
	bool isBright = false;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit RoomController2(const std::string &n = "rctrl2") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage(){
    	portName[rctrl_light_in] = "light_in2";
    	portName[rctrl_ambient_light_in] = "ambient_light_in";
    	//portName[rctrl_emerg_in] = "emergency_in2";
    	portName[rctrl_room_out] = "room_out2";
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
    	if(_state == IDLE) _outputMessage = MSG(portName[rctrl_room_out], 0);
    	if(_state == HALF) _outputMessage = MSG(portName[rctrl_room_out], 1);
    	if(_state == FULL) _outputMessage = MSG(portName[rctrl_room_out], 2);
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

    	if (msg.port == portName[rctrl_light_in]) {//sctrl_light_left_in]) {
			isOccupied = (msg.val == 1);
		} else if (msg.port == portName[rctrl_ambient_light_in]) {
			isBright = (msg.val == 1);
		}

    	if(isOccupied){
    		if (isBright){
    			_state = HALF;
    		} else {
    			_state = FULL;
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
    }

    void print()  noexcept {SWO_PrintString("rctrl2");}

};
}
}
}
}


#endif /* RoomController_HPP_ */
