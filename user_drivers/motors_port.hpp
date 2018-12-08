/*
 * motors_port.hpp
 *
 *  Created on: July 23, 2015
 *      Author: Daniella Niyonkuru
 */

#ifndef motors_port_HPP_
#define motors_port_HPP_


using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

template<class TIME, class MSG>
class MOVEL_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit MOVEL_OUT(const std::string &n = "motor1") noexcept : port<TIME, MSG>(n) {}//printf("M1 CREATED \n");
     void print() noexcept{} //printf("MOTOR 1 \n");
     bool pDriver(Value &v) const noexcept;
};

template<class TIME, class MSG>
class MOVER_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor2_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit MOVER_OUT(const std::string &n = "motor2") noexcept : port<TIME, MSG>(n) {}//printf("M2 CREATED \n");
     void print() noexcept{}//printf("MOTOR 2 \n");
     bool pDriver(Value &v) const noexcept;

};

#endif /* motors_port_HPP_ */
