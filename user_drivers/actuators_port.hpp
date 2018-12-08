/*
 * motors_port.hpp
 *
 *  Created on: July 23, 2015
 *      Author: Daniella Niyonkuru
 */

#ifndef actuators_port_HPP_
#define actuators_port_HPP_


using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

template<class TIME, class MSG>
class ROOM1_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit ROOM1_OUT(const std::string &n = "room1_out") noexcept : port<TIME, MSG>(n) {}//printf("M1 CREATED \n");
     void print() noexcept{} //printf("MOTOR 1 \n");
     bool pDriver(Value &v) const noexcept;
};

template<class TIME, class MSG>
class ROOM2_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor2_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit ROOM2_OUT(const std::string &n = "room2_out") noexcept : port<TIME, MSG>(n) {}//printf("M2 CREATED \n");
     void print() noexcept{}//printf("MOTOR 2 \n");
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class EMERGENCY1_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor2_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit EMERGENCY1_OUT(const std::string &n = "emergency1_out") noexcept : port<TIME, MSG>(n) {}//printf("M2 CREATED \n");
     void print() noexcept{}//printf("MOTOR 2 \n");
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class EMERGENCY2_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor2_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit EMERGENCY2_OUT(const std::string &n = "emergency2_out") noexcept : port<TIME, MSG>(n) {}//printf("M2 CREATED \n");
     void print() noexcept{}//printf("MOTOR 2 \n");
     bool pDriver(Value &v) const noexcept;

};

#endif /* actuators_port_HPP_ */
