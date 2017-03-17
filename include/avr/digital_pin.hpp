#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

/*

constexpr?
auto const pins_config = uno::configure_pins()(pin1,input)(pin2,output)(pin3,dynamic(output));

auto const pins = pins_config.initialize(); // only available operation.

pins(pin1).high();
auto val = pins(pin2).read();
pins(pin3).low();
pins(pin3).input().read(); // or pins(pin3).input(); pins(pin3).read();



 */

template < uint8_t PinID >
struct pin_tag
{
    static constexpr uint8_t id = PinID;
    constexpr pin_tag() {}
};

#define PIN_TAG(X) constexpr pin_tag<X> pin ## X

PIN_TAG(1);
PIN_TAG(2);
PIN_TAG(3);
PIN_TAG(4);
PIN_TAG(5);
PIN_TAG(6);
PIN_TAG(7);
PIN_TAG(8);
PIN_TAG(9);
PIN_TAG(10);
PIN_TAG(11);

template < uint8_t PinID, typename Arch >
struct input_pin
{
    int read() const
    {
        return arch.read(pin);
    }

    constexpr input_pin(Arch a) : pin(), arch(a) {}

    pin_tag<PinID> pin;
    Arch arch;
};

template < uint8_t PinID, typename Arch >
struct output_pin
{
    void high() const { arch.high(pin); }
    void low() const { arch.low(pin); }

    pin_tag<PinID> pin;
    Arch arch;

    constexpr output_pin(Arch a) : arch(a) {}
};

struct input_pin_initializer
{
    template < uint8_t PinID, typename Arch >
    constexpr static input_pin<PinID, Arch> initialize(pin_tag<PinID> pin, Arch arch)
    {
        return arch.initialize(pin, arch.input);
    }
};

struct output_pin_initializer
{
    template < typename PinTag, typename Arch >
    constexpr static output_pin<PinTag::id, Arch> initialize(PinTag pin, Arch arch)
    {
        return arch.initialize(pin, arch.output);
    }
};

struct unconfigured_pin
{
    constexpr static input_pin_initializer input()
    {
        return input_pin_initializer{};
    }

    constexpr static output_pin_initializer output()
    {
        return output_pin_initializer{};
    }
};



#endif
