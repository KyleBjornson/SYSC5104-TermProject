/*
 * actuators_port.hpp
 *
 *  Created on: Dec 9, 2018
 *      Author: Kyle and Ben
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
     * @brief room1 constructor.
     *
     * @param n name assigned to the port
     */
     explicit ROOM1_OUT(const std::string &n = "room_out1") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(Value &v) const noexcept;
};

template<class TIME, class MSG>
class ROOM2_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief room2 constructor.
     *
     * @param n name assigned to the port
     */
     explicit ROOM2_OUT(const std::string &n = "room_out2") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class EMERGENCY1_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief emergency1 constructor.
     *
     * @param n name assigned to the port
     */
     explicit EMERGENCY1_OUT(const std::string &n = "emerg_out1") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class EMERGENCY2_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief emergency2 constructor.
     *
     * @param n name assigned to the port
     */
     explicit EMERGENCY2_OUT(const std::string &n = "emerg_out2") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(Value &v) const noexcept;

};

#endif /* actuators_port_HPP_ */
