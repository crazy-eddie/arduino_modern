#ifndef HARDWARE_ARCH_AVR_HPP
#define HARDWARE_ARCH_AVR_HPP

#include "avr/digital_port.hpp"
#include "avr/analog_converter.hpp"
#include "../../mpl/collection.hpp"


namespace crazy_arduino { namespace hardware { namespace arch {

using namespace avr_detail;

template < typename Pin, typename Device >
struct pin_function
{
    constexpr pin_function(){}
};

template < typename Pins = mpl::collection >
struct pin_function_table
{
    constexpr pin_function_table() {}

    template < typename Pin, typename Function >
    static constexpr auto attach_pin(Pin,Function)
    {
        constexpr auto new_pins = Pins::append(pin_function<Pin,Function>{});
        return pin_function_table<decltype(new_pins)>{};
    }

    template < typename Pin, typename Function, typename ... Remain >
    static constexpr auto attach_pin(Pin pin,Function fun,Remain... rem)
    {
        return attach_pin(pin,fun).attach_pin(pin,rem...);
    }
};

namespace avr
{

constexpr auto PB = port<'B'>();
constexpr auto PC = port<'C'>();
constexpr auto PD = port<'D'>();

constexpr auto ADC = analog_converter{};

template < int > struct non_programmable { constexpr non_programmable(){}};

constexpr auto VCC = non_programmable<0>{};
constexpr auto GND = non_programmable<1>{};
constexpr auto AVCC = non_programmable<2>{};
constexpr auto AREF = non_programmable<3>{};

// static constexpr auto adc = analog()
template < typename Pin, typename ... Functions >
constexpr auto attach_pin(Pin pin, Functions ... fun)
{
    return pin_function_table<>{}.attach_pin(pin,fun...);
}

}

using namespace avr;


}}}

#endif
