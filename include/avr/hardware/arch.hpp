#ifndef AVR_HARDWARE_ARCH_HPP
#define AVR_HARDWARE_ARCH_HPP

#include "configurator.hpp"

namespace avr { namespace hardware {

template < typename PinTag, typename Port, typename Mask >
struct pin_description
{
    template < typename P >
    static constexpr bool matches_tag(P) { return false; }

    static constexpr bool matches_tag(PinTag) { return true; }

    constexpr pin_description(){}

    using pin_t = PinTag;
    using port_t = Port;
    using mask_t = Mask;

    static constexpr pin_t pin = pin_t{};
    static constexpr port_t port = port_t{};
    static constexpr uint8_t mask = Mask::value;
};

template < typename PinTag, typename Port, typename Mask >
constexpr pin_description<PinTag,Port,Mask> create_pin(PinTag,Port,Mask)
{
    return pin_description<PinTag,Port,Mask>{};
}

template < typename ... Pins >
struct pin_configuration
{
    constexpr pin_configuration(){}

    template < typename P >
    static constexpr bool has_pin(P) { return false; }

    template < typename PinDescription >
    static constexpr pin_configuration<PinDescription> append_pin(PinDescription)
    {
        return pin_configuration<PinDescription>{};
    }

    template < typename IO >
    static constexpr configurator<IO> fin(IO) { return configurator<IO>{}; }
};

template < typename PinDescription, typename ... Remaining >
struct pin_configuration<PinDescription, Remaining...>
{
    constexpr pin_configuration() {}

    template < typename PinTag >
    static constexpr bool has_pin(PinTag pin)
    {
        return PinDescription::matches_tag(pin) ? true : pin_configuration<Remaining...>::has_pin(pin);
    }

    template < typename NewDescription >
    static constexpr pin_configuration<PinDescription, Remaining..., NewDescription> append_pin(NewDescription)
    {
        return pin_configuration<PinDescription, Remaining..., NewDescription>{};
    }

    template < typename IO >
    static constexpr configurator<IO, PinDescription,Remaining...> fin(IO)
    {
        return configurator<IO, PinDescription,Remaining...>{};
    }
};


template < typename RawOps >
struct basic_ops : RawOps
{
    template < typename Pin >
    static void set_mode(Pin pin, pin_config::input_tag)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port.mode_register()) &= ~pin.mask;
        *(pin.port.output_register()) &= ~pin.mask;

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void set_mode(Pin pin, pin_config::output_tag)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port.mode_register()) |= pin.mask;

        basic_ops::status_register() = old;
    }

    template < typename Pin >
    static void high(Pin pin)
    {
        auto old = basic_ops::status_register();
        basic_ops::disable_interrupts();

        *(pin.port.output_register()) |= pin.mask;

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
        return *pin.port.input_register() & pin.mask;
    }

};



template < typename RawOps, typename PinConfiguration = pin_configuration<> >
struct arch__ : RawOps
{
    template < typename PinDesc >
    constexpr auto register_pin(PinDesc desc) -> arch__<RawOps, decltype(PinConfiguration::append_pin(desc))>
    {
        return arch__<RawOps, decltype(PinConfiguration::append_pin(desc))>{};
    }

    template < typename Pin, typename Port, typename Mask >
    constexpr auto register_pin(Pin pin, Port port, Mask mask) -> decltype(register_pin(create_pin(pin,port,mask)))
    {
        return register_pin(create_pin(pin,port,mask));
    }

    template < typename Pin >
    constexpr bool has_pin(Pin pin)
    {
        return PinConfiguration::has_pin(pin);
    }

    //constexpr configurator< fin() { return configurator{}; }
    constexpr auto fin() -> decltype(PinConfiguration::fin(RawOps{}))
    {
        return PinConfiguration::fin(RawOps{});
    }

    constexpr arch__() {}
};

template < typename RawOps >
using arch_ = arch__<basic_ops<RawOps>>;


}}


#endif
