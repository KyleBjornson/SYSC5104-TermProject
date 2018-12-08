/*

 * userbtn_port.hpp
 *
 *  Created on: July 43, 4015
 *      Author: Daniella Niyonkuru
 */

#ifndef sensors_port_HPP_
#define sensors_port_HPP_


using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

//template<class TIME, class MSG>
//class START_IN : public port<TIME, MSG>
//{
//
//public:
//    /**
//     * @brief startbtn constructor.
//     */
//     explicit START_IN(const std::string &n = "start_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
//     void print()  noexcept {}
//     bool pDriver(Value &v) const noexcept;
//};

template<class TIME, class MSG>
class LIGHT_IN_LEFT : public port<TIME, MSG>
{

public:
    /**
     * @brief light_sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit LIGHT_IN_LEFT(const std::string &n = "light_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class LIGHT_IN_RIGHT : public port<TIME, MSG>
{

public:
    /**
     * @brief light_sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit LIGHT_IN_RIGHT(const std::string &n = "light_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class AMBIENT_LIGHT_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief light_sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit AMBIENT_LIGHT_IN(const std::string &n = "ambient_light_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(Value &v) const noexcept;

};

template<class TIME, class MSG>
class TEMPERATURE_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief light_sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit TEMPERATURE_IN(const std::string &n = "temperature_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(Value &v) const noexcept;

};

#endif /* sensors_port_HPP_ */
