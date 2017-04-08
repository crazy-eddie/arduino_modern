#ifndef AVR_HARDWARE_CONFIGURATOR_HPP
#define AVR_HARDWARE_CONFIGURATOR_HPP

#include "../../mpl/collection.hpp"

namespace avr { namespace hardware {

namespace detail_ {

template < typename IO
         , typename AvailablePins
         , typename ConfiguredPins = mpl::lookup_collection
         >
struct configurator
{
    template < typename Pin >
    static constexpr bool available(Pin pin)
    {
        return AvailablePins::has(pin);
    }

    template < typename Pin, typename Mode >
    static constexpr auto set_mode(Pin pin, Mode mode)
    {
        return create( AvailablePins::remove(pin)
                     , ConfiguredPins::add(pin, make_config(pin,mode)));
    }

    template < typename Pin >
    static constexpr auto mode(Pin pin)
    {
        return ConfiguredPins::get(pin).mode; // invalid use of void?  Pin isn't configured.
    }

    static constexpr IO io() { return IO{}; }

    constexpr ConfiguredPins configured() { return ConfiguredPins{}; }

    constexpr configurator() {}

private:

    template < typename PinDesc, typename Mode >
    struct pin_config
    {
        constexpr pin_config() {}

        static constexpr auto pin_desc = PinDesc{};
        static constexpr auto mode = Mode{};
    };

    template < typename Pin, typename Mode >
    static constexpr auto make_config(Pin pin, Mode mode)
    {
        using desc = decltype(AvailablePins::get(pin));
        return pin_config<desc,Mode>{};
    }

    template < typename AP, typename CP >
    static constexpr auto create(AP ap, CP cp)
    {
        return configurator<IO,AP,CP>{};
    }
};

}

template < typename PlatformBuilder >
constexpr auto describe_platform(PlatformBuilder builder)
{
    return detail_::configurator<decltype(builder.io()), decltype(builder.pins())>{};
}


}}



#endif
