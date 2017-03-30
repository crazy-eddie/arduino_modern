#ifndef AVR_HARDWARE_INITIALIZE_HPP
#define AVR_HARDWARE_INITIALIZE_HPP

#include "configurator.hpp"
#include "driver.hpp"

namespace avr { namespace hardware {

template < typename IO, typename Pin, typename Mode >
void set_mode(IO io, Pin pin, Mode mode)
{
    io.set_mode(pin,mode);
}

template < typename IO, typename Pin > void set_mode(IO,Pin,unset_mode) {}


template < typename IO >
void initialize_pins(IO, pin_collection<>) {}

template < typename IO, typename PinConfig, typename ... Remaining >
void initialize_pins(IO io, pin_collection<PinConfig, Remaining...> pins)
{
    set_mode(io, PinConfig::pin, PinConfig::mode);
    initialize_pins(io, pin_collection<Remaining...>{});
}


template < typename ... PinConfig >
struct active_pins
{
    template < typename Collection, typename Config, typename Mode = typename Config::mode_t >
    struct append_active;

    // not active...
    template < typename ... Entries, typename Config >
    struct append_active<pin_collection<Entries...>, Config, unset_mode>
    {
        using type = pin_collection<Entries...>;
    };

    template < typename ... Entries, typename Config, typename Mode >
    struct append_active<pin_collection<Entries...>,Config,Mode>
    {
        using type = pin_collection<Entries...,Config>;
    };

    template < typename Collection, typename Pin, typename ... Pins >
    struct build_collection
    {
        using type = typename append_active<typename build_collection<Collection, Pins...>::type, Pin>::type;
    };

    template < typename Collection, typename Pin >
    struct build_collection<Collection, Pin>
    {
        using type = typename append_active<Collection, Pin>::type;
    };

    using type = typename build_collection<pin_collection<>, PinConfig...>::type;
};

template < typename Pins >
struct create_pins;

template < typename ... Pins >
struct create_pins<pin_collection<Pins...>> : create_drivers<Pins...> {};

template < typename IO, typename ... Pins >
driver_<IO, create_pins<typename active_pins<Pins...>::type>> initialize(configurator_<IO, Pins...> conf)
{
    using active = typename active_pins<Pins...>::type;
    initialize_pins(conf.io, active{});
    return driver_<IO, create_pins<active>>{};
}

}}

#endif
