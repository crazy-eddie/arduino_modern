#ifndef AVR_HARDWARE_DRIVER_HPP
#define AVR_HARDWARE_DRIVER_HPP

#include "tags.hpp"

namespace avr { namespace hardware {

template < typename PinDesc >
struct input_pin
{
    template < typename IO >
    static bool read(IO)
    {
        return IO::read(PinDesc{});
    }

    using pin_t = PinDesc;
    using type = input_pin;
};

template < typename PinDesc >
struct output_pin
{
    template < typename IO >
    static void high(IO)
    {
        IO::high(PinDesc{});
    }

    template < typename IO >
    static void low(IO)
    {
        IO::low(PinDesc{});
    }

    using pin_t = PinDesc;
    using type = output_pin;
};

template < typename PinDesc, typename Mode > struct pin_type;

template < typename PinDesc >
struct pin_type<PinDesc, pin_config::input_tag>
{
    using type = input_pin<PinDesc>;
};
template < typename PinDesc >
struct pin_type<PinDesc,pin_config::output_tag>
{
    using type = output_pin<PinDesc>;
};

template < typename Pin, typename ... Drivers >
struct get_driver;

template < bool b, typename True, typename False > struct if_ { using type = False; };
template < typename True, typename False >
struct if_<true,True,False> { using type = True; };

template < typename T > struct ident { using type = T; };

template < typename Pin, typename Driver, typename ... Remaining >
struct get_driver<Pin, Driver, Remaining...>
    : if_<Driver::pin_t::matches_tag(Pin{}), ident<Driver>, get_driver<Pin,Remaining...>>::type
{
};

template < typename ... PinDrivers >
struct pin_drivers
{
    template < typename IO, typename Pin >
    static void high(IO io,Pin)
    {
        using driver = typename get_driver<Pin,PinDrivers...>::type;
        driver::high(io);
    }

    template < typename IO, typename Pin >
    static void low(IO io, Pin)
    {
        using driver = typename get_driver<Pin,PinDrivers...>::type;
        driver::low(io);
    }

    template < typename IO, typename Pin >
    static bool read(IO io, Pin)
    {
        using driver = typename get_driver<Pin,PinDrivers...>::type;
        return driver::read(io);
    }
};

template < typename ... Pins >
using create_drivers = pin_drivers<typename pin_type<typename Pins::pin_t, typename Pins::mode_t>::type ...>;

template < typename IO, typename Pins >
struct driver_
{
    static constexpr auto io = IO{};

    template < typename Pin >
    static void high(Pin pin) { Pins::high(io, pin); }

    template < typename Pin >
    static void low(Pin pin) { Pins::low(io,pin); }

    template < typename Pin >
    static bool read(Pin pin) { return Pins::read(io,pin); }
};


}}


#endif
