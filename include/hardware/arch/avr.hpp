#ifndef HARDWARE_ARCH_AVR_HPP
#define HARDWARE_ARCH_AVR_HPP

#include "avr/digital_port.hpp"
#include "avr/analog_converter.hpp"
#include "../../mpl/collection.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace avr {

struct non_programmable : generic::module<non_programmable, 1U>
{
    constexpr non_programmable() {}
};

constexpr auto NP = non_programmable{};

constexpr auto VCC = NP[0_c];
constexpr auto GND = NP[1_c];
constexpr auto AVCC = NP[2_c];
constexpr auto AREF = NP[3_c];


}}}}

#endif
