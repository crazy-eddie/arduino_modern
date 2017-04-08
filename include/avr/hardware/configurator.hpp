#ifndef AVR_HARDWARE_CONFIGURATOR_HPP
#define AVR_HARDWARE_CONFIGURATOR_HPP

#include "../../mpl/collection.hpp"

namespace avr { namespace hardware {

namespace detail_ {

template < typename AvailablePins
         , typename ConfiguredPins = mpl::lookup_collection
         >
struct configurator
{
    template < typename Pin >
    constexpr bool available(Pin pin) const
    {
        return available_pins.has(pin);
    }

    template < typename Pin, typename Mode >
    constexpr auto set_mode(Pin pin, Mode mode) const
    {
        using remaining = decltype(available_pins.remove(pin));
        using config = decltype(configured_pins.add(pin, make_config(pin,mode)));
        return configurator<remaining, config>{available_pins.remove(pin), configured_pins.add(pin, make_config(pin,mode))};
    }

    template < typename Pin >
    constexpr auto mode(Pin pin) const
    {
        return configured_pins[pin].mode; // invalid use of void?  Pin isn't configured.
    }

    constexpr configurator(AvailablePins p) : available_pins{p} {}
    constexpr configurator(AvailablePins ap, ConfiguredPins cp)
        : available_pins{ap}
        , configured_pins{cp}
    {}

private:
    AvailablePins available_pins;
    ConfiguredPins configured_pins;

    template < typename PinDesc, typename Mode >
    struct pin_config
    {
        constexpr pin_config(PinDesc p) : pin_desc{p}, mode{} {}

        PinDesc pin_desc;
        Mode mode;
    };

    template < typename Pin, typename Mode >
    constexpr auto make_config(Pin pin, Mode mode) const
    {
        using desc = decltype(available_pins[pin]);
        return pin_config<desc,Mode>{available_pins[pin]};
    }
};

}

template < typename PlatformBuilder >
constexpr auto describe_platform(PlatformBuilder builder)
{
    return detail_::configurator<decltype(builder.pins())>{builder.pins()};
}


}}



#endif
