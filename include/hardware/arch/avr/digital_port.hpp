#ifndef  HARDWARE_ARCH_AVR_DIGITAL_PORT_HPP
#define  HARDWARE_ARCH_AVR_DIGITAL_PORT_HPP

#include "../generic/module.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace avr {

using namespace generic;


namespace detail_ {

struct digital_io : generic::module<digital_io, 2U> { constexpr digital_io() {} };

}

constexpr auto digital_io = detail_::digital_io{};

constexpr auto PB = digital_io[1_c];
constexpr auto PC = digital_io[2_c];
constexpr auto PD = digital_io[3_c];

template < typename Port, typename PinIdx >
using digital_pin = function<detail_::digital_io, Port, PinIdx>;

}}}}

#endif
