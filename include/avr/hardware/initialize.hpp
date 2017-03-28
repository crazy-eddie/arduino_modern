#ifndef AVR_HARDWARE_INITIALIZE_HPP
#define AVR_HARDWARE_INITIALIZE_HPP

#include "configurator.hpp"

namespace avr { namespace hardware {

template < typename IO, typename Pin, typename Mode >
void set_mode(IO io, Pin pin, Mode mode)
{
    io.set_mode(pin,mode);
}

template < typename IO, typename Pin > void set_mode(IO,Pin,unset_mode) {}

template < typename IO >
void initialize_pins(configurator_<IO>) {}

template < typename IO, typename PinConfig, typename ... Remaining >
void initialize_pins(configurator_<IO, PinConfig, Remaining...>)
{
    set_mode(IO{}, PinConfig::pin, PinConfig::mode);
    initialize_pins(configurator_<IO, Remaining...>{});
}

template < typename Config >
bool initialize(Config conf)
{
    initialize_pins(conf);
    return false;
}

}}

#endif
