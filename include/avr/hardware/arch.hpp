#ifndef AVR_HARDWARE_ARCH_HPP
#define AVR_HARDWARE_ARCH_HPP

namespace avr { namespace hardware {

template < typename RawOps >
struct arch_ : RawOps
{
    template < typename Pin >
    static void set_mode(Pin pin, pin_config::input_tag)
    {
        auto old = arch_::status_register();
        arch_::disable_interrupts();

        *(pin.port.mode_register()) &= ~pin.mask;
        *(pin.port.output_register()) &= ~pin.mask;

        arch_::status_register() = old;
    }

    template < typename Pin >
    static void set_mode(Pin pin, pin_config::output_tag)
    {
        auto old = arch_::status_register();
        arch_::disable_interrupts();

        *(pin.port.mode_register()) |= pin.mask;

        arch_::status_register() = old;
    }

    template < typename Pin >
    static void high(Pin pin)
    {
        auto old = arch_::status_register();
        arch_::disable_interrupts();

        *(pin.port.output_register()) |= pin.mask;

        arch_::status_register() = old;
    }

    template < typename Pin >
    static void low(Pin pin)
    {
        auto old = arch_::status_register();
        arch_::disable_interrupts();

        *(pin.port.output_register()) &= ~pin.mask;

        arch_::status_register() = old;
    }

    template < typename Pin >
    static bool read(Pin pin)
    {
        return *pin.port.input_register() & pin.mask;
    }

    constexpr arch_() {}
};


}}


#endif
