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
    enum State {IDLE, PREP_RX, WAIT_DATA, TX_DATA, PREP_STOP};
    enum Port {sctrl_start_in, sctrl_light_in, sctrl_mctrl_in, sctrl_mctrl_out, sctrl_start_out};
    std::string portName[5];
    State _state;
    MSG _outputMessage1,_outputMessage2;
	//Variables:
    int sensor_input = 0;
	TIME scTxTime = TIME(00,00,00,050);
	TIME scRxPrepTime = TIME(00,00,00,050);
	const TIME infinity=boost::simulation::model<TIME>::infinity;



public:
    /**
     * @brief SensorController constructor.
     */
    explicit SensorController(const std::string &n = "sctrl") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage1(), _outputMessage2() {
    	portName[0] = "start_in"; portName[1] = "light_in"; portName[2] = "MCTRL_IN"; portName[3] = "SCTRL_OUT"; portName[4] = "START_OUT";
    }

    /**
     * @brief internal function.
     */
    void internal() noexcept {
    	switch (_state){
    		case PREP_STOP:
    			_state = IDLE;
    			_next = infinity;
    			break;

    		case PREP_RX:
    		case TX_DATA:
    			_state = WAIT_DATA;
    			_next = infinity;
    			break;
    	}

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
    	switch (_state){

    			case PREP_STOP:
					_outputMessage1 = MSG(portName[sctrl_start_out], STOP_PROC); //Stop Light Sensor
					_outputMessage2 = MSG(portName[sctrl_mctrl_out], STOP_PROC); //Stop Movement Ctrl
					return std::vector<MSG>{_outputMessage1, _outputMessage2};

    			case PREP_RX:
					_outputMessage1 = MSG(portName[sctrl_start_out], START_PROC); //Start Light Sensor
					return std::vector<MSG>{_outputMessage1};

    			case TX_DATA: {
    				int output_val;

    				if(sensor_input == DARK)
    					output_val = ON_TRACK;
    				else if(sensor_input == BRIGHT)
    					output_val = OFF_TRACK;

    				_outputMessage1 = MSG(portName[sctrl_mctrl_out], output_val); //Send feedback to Movement Ctrl
    				return std::vector<MSG>{_outputMessage1};
    			}
    		};
    	return std::vector<MSG>{};

    }
    /**
     * @brief external function
     * @param msg external input message.
     * @param t time the external input is received.
     */
    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

    	MSG msg = mb.back();

    	if (msg.port == portName[sctrl_start_in]){
    			if(_state == IDLE && msg.val == START_PROC){
    				_state = PREP_RX;
    				_next = scRxPrepTime;
    			}

    			else if (msg.val == STOP_PROC) {
    				_state = PREP_STOP;
    				_next = Time::Zero;
    			}
    		}
    		else if (msg.port == portName[sctrl_light_in]){
    			if(_state == WAIT_DATA) {
    				sensor_input = static_cast<int>(msg.val);

    				if(sensor_input == ALL_DARK) {
    					_state = PREP_STOP;
    					_next = Time::Zero;
    				} else {
    					_state = TX_DATA;
    					_next = scTxTime;
    				}
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
