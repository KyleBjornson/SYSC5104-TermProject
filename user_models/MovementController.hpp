///*
// * MovementController.hpp
// *
// *  Created on: July 25, 2015
// *      Author: Daniella
// */
//
//#ifndef MovementController_HPP_
//#define MovementController_HPP_
//
//#include <boost/any.hpp>
//#include <boost/simulation/pdevs/atomic.hpp>
//#include "commonH.h"
//#include "SWO.h"
//
//namespace boost {
//namespace simulation {
//namespace pdevs {
//namespace basic_models {
///**
// * @brief MovementController PDEVS Model
// *
// * MovementController PDEVS Model():
// * - X = {(mctrl_lsdata_in, {ON_TRACK, TURN_LEFT, TURN_RIGHT}); {(mctrl_proxydata_in, { NO_OBSTACLE,  STOP })}
// * - Y = {(mctrl_motor1_out, {goFwd, goBkwd stop}); (mctrl_motor2_out, {goFwd, goBkwd, stop})}
// * - S = {“PREP_MOVE_FWD,” “MOVE_FWD,” “PREP_TURN_LEFT,” TURN_LEFT “PREP_TURN_RIGHT, TURN_RIGHT” “PREP_STOP,” “STOP”, "IDLE"}
// * - internal -> See DEVS Spec Doc
// * - external -> See DEVS Spec Doc
// * - out      -> See DEVS Spec Doc
// * - advance  -> See DEVS Spec Doc
//*/
//template<class TIME, class MSG>
//class MovementController : public atomic<TIME, MSG>
//{
//    TIME _next;
//    std::vector<MSG> _outvalue;
//private:
//    enum State {IDLE, PREP_MOVE_FWD, MOVE_FWD, MX_STOP, WAIT_DATA, PREP_TURN, TURN_ALPHA, PREP_STOP};
//    enum Port {mctrl_sctrl_in, mctrl_sctrl_out, mctrl_moveL_out, mctrl_moveR_out};
//    std::string portName[4];
//	const TIME infinity = boost::simulation::model<TIME>::infinity;
//    MSG _outputMessage1,_outputMessage2;
//    State _state;
//    // Variable
//    int sctrl_input = 0;
//	// Prep time
//	TIME movePrepTime = TIME(00,00,00,050);
//	TIME turnTime = TIME(00,00,01,000);
//
//
//public:
//    /**
//     * @brief MovementController constructor.
//     *
//     */
//    explicit MovementController(const std::string &n = "mctrl") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessage1(), _outputMessage2() {
//    	portName[0] = "SCTRL_OUT"; portName[1] = "MCTRL_OUT"; portName[2] = "motor1"; portName[3] = "motor2";
//    	printf("MCTRL CREATED \n");
//    }
//
//    /**
//     * @brief internal function.
//     */
//    void internal() noexcept {
//    	switch (_state){
//    		case PREP_MOVE_FWD:
//    			_state = MOVE_FWD;
//    			_next = infinity;
//    			break;
//
//    		case MX_STOP:
//    			_state = PREP_TURN;
//    			_next = movePrepTime;
//    			break;
//
//    		case PREP_TURN:
//    			_state = TURN_ALPHA;
//    			_next = turnTime;
//    			break;
//
//    		case TURN_ALPHA:
//    			_state = WAIT_DATA;
//    			_next = infinity;
//    			break;
//
//    		case PREP_STOP:
//    			_state = IDLE;
//    			_next = infinity;
//    			break;
//
//    		default:
//    			break;
//    	}
//    }
//    /**
//     * @brief advance function.
//     * @return Time until next internal event.
//     */
//    TIME advance() const noexcept {
//    	return _next;
//    }
//    /**
//     * @brief out function.
//     * @return MSG defined below.
//     */
//    std::vector<MSG> out() const noexcept {
//    	if (_state==PREP_MOVE_FWD)
//    	{
//			_outputMessage1 = MSG(portName[mctrl_moveR_out], COMMON_H::O_GO_FWD);
//			_outputMessage2 = MSG(portName[mctrl_moveL_out], COMMON_H::O_GO_FWD);
//			return std::vector<MSG>{_outputMessage1, _outputMessage2};
//
//    	}
//
//    	else if(_state== MX_STOP || _state==TURN_ALPHA || _state== PREP_STOP)
//    	{
//			_outputMessage1 = MSG(portName[mctrl_moveR_out], COMMON_H::O_STOP);
//			_outputMessage2 = MSG(portName[mctrl_moveL_out], COMMON_H::O_STOP);
//			return std::vector<MSG>{_outputMessage1, _outputMessage2};
//    	}
//
//    	else if (_state== PREP_TURN)
//    	{
//			_outputMessage1 = MSG(portName[mctrl_moveR_out], COMMON_H::O_GO_FWD);
//			_outputMessage2 = MSG(portName[mctrl_moveL_out], COMMON_H::O_GO_REV);
//			return std::vector<MSG>{_outputMessage1, _outputMessage2};
//    	}
//
//    	return std::vector<MSG>{};
//    }
//    /**
//     * @brief external function will set the new state depending on the value of the input.
//     * @param msg external input message.
//     * @param t time the external input is received.
//     */
//    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {
//
//    	MSG msg = mb.back();
//    	if (msg.port == portName[mctrl_sctrl_in]) {
//
//    		sctrl_input = static_cast<int>(msg.val);
//
//    		if (sctrl_input == STOP_PROC) {
//    			_state = PREP_STOP;
//    			_next = Time::Zero;
//    		}
//
//    		else if (sctrl_input == ON_TRACK) {
//
//    			if (_state == WAIT_DATA || _state == IDLE || _state == TURN_ALPHA) {
//    				_state = PREP_MOVE_FWD;
//    				_next = movePrepTime;
//    			}
//    		}
//
//    		else if (sctrl_input == OFF_TRACK) {
//
//    			if (_state == MOVE_FWD) {
//    				_state = MX_STOP;
//    				_next = Time::Zero;
//    			}
//    			else if (_state == WAIT_DATA || _state == IDLE) {
//    				_state = PREP_TURN;
//    				_next = movePrepTime;
//    			}
//    		}
//    	}
//    }
//
//    /**
//     * @brief confluence function.
//     * Execute the internal.
//     *
//     * @param msg
//     * @param t time the external input is confluent with an internal transition.
//     */
//    void confluence(const std::vector<MSG>& mb, const TIME& t)  noexcept  {
//    	internal();
//    }
//
//    void print()  noexcept {
//    	SWO_PrintString("mctrl");
//    }
//
//};
//
//}
//}
//}
//}
//
//
//#endif /* MovementController_HPP_ */
