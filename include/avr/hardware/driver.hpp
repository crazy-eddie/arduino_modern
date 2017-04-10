#ifndef AVR_HARDWARE_DRIVER_HPP
#define AVR_HARDWARE_DRIVER_HPP

#include "tags.hpp"
#include "pin.hpp"
#include "../../mpl/util.hpp"

namespace avr { namespace hardware {

namespace detail_ {



template < typename IO
         , typename InputPins = mpl::lookup_collection
         , typename OutputPins = mpl::lookup_collection >
struct driver
{
    constexpr driver() {}

    template < typename ... Pin >
    void high(Pin ... pins) const
    {
        constexpr auto pin_collection = collate_pins(OutputPins{}, pins...);
        mpl::for_each( pin_collection.begin()
                     , pin_collection.end()
                     , [](auto pin_port) { IO::high(hardware::pin(pin_port.key(), pin_port.value())); });
    }

    template < typename ... Pin >
    void low(Pin ... pins) const
    {
        constexpr auto pin_collection = collate_pins(OutputPins{}, pins...);
        mpl::for_each( pin_collection.begin()
                     , pin_collection.end()
                     , [](auto pin_port) { IO::low(hardware::pin(pin_port.key(), pin_port.value())); });
    }

    template < typename ... Pin >
    void toggle(Pin ... pins) const
    {
        constexpr auto pin_collection = collate_pins(OutputPins{}, pins...);
        mpl::for_each( pin_collection.begin()
                     , pin_collection.end()
                     , [](auto pin_port) { IO::toggle(hardware::pin(pin_port.key(), pin_port.value())); });
    }

    template < typename Pin >
    bool read(Pin pin) const
    {
        return IO::read(InputPins::get(pin));
    }

    template < typename Pin, typename Desc >
    constexpr auto add_pin(Pin pin, Desc desc, pin_config::input_tag) const
    {
        using new_input = decltype(InputPins::insert(pin, desc));

        return driver<IO, new_input, OutputPins>{};
    }

    template < typename Pin, typename Desc >
    constexpr auto add_pin(Pin pin, Desc desc, pin_config::output_tag) const
    {
        using new_output = decltype(OutputPins::insert(pin,desc));

        return driver<IO, InputPins, new_output>{};
    }

};

// TODO: accumulate
template < typename Driver, typename End >
constexpr auto const create_driver(Driver driver, End,End)
{
    return driver;
}

template < typename Driver, typename Beg, typename End >
constexpr auto const create_driver(Driver driver, Beg beg, End end)
{
    return create_driver(driver.add_pin( beg.key()
                                       , beg.deref().value().pin_desc
                                       , beg.deref().value().mode), beg.next(), end);
}

template < typename IO >
constexpr auto const new_driver(IO)
{
    return driver<IO>{};
}

}

template < typename HardwareConfig >
auto const create_driver(HardwareConfig cfg)
{
    return detail_::create_driver( detail_::new_driver(cfg.io())
                                 , cfg.configured().begin()
                                 , cfg.configured().end() );
}


#if 0
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

#endif

}}


#endif
