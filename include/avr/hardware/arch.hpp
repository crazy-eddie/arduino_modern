#ifndef AVR_HARDWARE_ARCH_HPP
#define AVR_HARDWARE_ARCH_HPP

#include "../../mpl/collection.hpp"
#include "pin.hpp"

namespace avr { namespace hardware {


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
    static void low(Pin pin)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port.output_register()) &= ~pin.mask;

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
    constexpr auto register_pin(Pin p, Port port, Mask mask) const
    {
        return create(p, pins.add(p, pin(port,mask)));
    }

    template < typename Pin >
    constexpr bool has_pin(Pin pin) const
    {
        return pins.has(pin);
    }

    constexpr arch__() {}
    constexpr arch__(PinConfiguration p) : pins(p) {}

private:
    PinConfiguration pins;

    template < typename Pin, typename NewPins >
    constexpr auto create(Pin, NewPins p) const
    {
        return arch__<RawOps,NewPins>{p};
    }
};

template < typename RawOps >
using arch_ = arch__<basic_ops<RawOps>>;


}}


#endif
