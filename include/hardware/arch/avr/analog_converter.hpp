#ifndef  HARDWARE_ARCH_AVR_ANALOG_CONVERTER_HPP
#define  HARDWARE_ARCH_AVR_ANALOG_CONVERTER_HPP

#include "../generic/module.hpp"


namespace crazy_arduino { namespace hardware { namespace arch { namespace avr {

using namespace generic;

namespace detail_ {

struct analog_converter : module<analog_converter,1>
{
    constexpr analog_converter(){}

};

}

constexpr auto ADC = detail_::analog_converter{};

template < typename ChanIdx >
using adc_channel = function<detail_::analog_converter, ChanIdx>;

}}}}

#endif
