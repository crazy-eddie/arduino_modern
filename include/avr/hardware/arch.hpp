#ifndef AVR_HARDWARE_ARCH_HPP
#define AVR_HARDWARE_ARCH_HPP

#include "../../mpl/collection.hpp"
#include "pin.hpp"

namespace avr { namespace hardware {

// TODO: Would be nice to ensure a pin can't be registered with port/mask config already used.
//       Also if the port is full.

template < typename RawOps >
struct basic_ops : RawOps
{
    template < typename Pin >
    static void set_mode(Pin pin, pin_config::input_tag)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port().mode_register()) &= ~pin.mask();
        *(pin.port().output_register()) &= ~pin.mask();

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void set_mode(Pin pin, pin_config::output_tag)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port().mode_register()) |= pin.mask();

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void high(Pin pin)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port().output_register()) |= pin.mask();

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void toggle(Pin pin)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port().output_register()) ^= pin.mask();

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void low(Pin pin)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port().output_register()) &= ~pin.mask();

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static bool read(Pin pin)
    {
        return *pin.port().input_register() & pin.mask();
    }

};


template < typename RawOps, typename PinConfiguration = mpl::lookup_collection >
struct arch__
{
    using ops = RawOps;

    template < typename Pin, typename Port, typename Mask >
    static constexpr auto register_pin(Pin p, Port port, Mask mask)
    {
        return create(p, PinConfiguration::insert(p, pin(port,mask)));
    }

    template < typename Pin >
    static constexpr bool has_pin(Pin pin)
    {
        return PinConfiguration::has(pin);
    }

    static constexpr PinConfiguration pins() { return PinConfiguration{}; }

    static constexpr RawOps io() { return RawOps{}; }

    constexpr arch__() {}

    template < typename Pin, typename NewPins >
    static constexpr auto create(Pin, NewPins)
    {
        return arch__<RawOps,NewPins>{};
    }
};

template < typename RawOps >
using arch_ = arch__<basic_ops<RawOps>>;


}}


#endif
