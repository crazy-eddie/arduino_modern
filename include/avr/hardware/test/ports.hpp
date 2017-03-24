#ifndef AVR_HARDWARE_TEST_PORTS_HPP
#define AVR_HARDWARE_TEST_PORTS_HPP

namespace avr { namespace hardware { namespace test {

template < typename Port, typename Mask >
struct pin
{
    static Port port;
    static uint8_t const mask = Mask::value;
};

template <int>
struct port
{
    static uint8_t* mode_register() { return &mode; }
    static uint8_t* input_register() { return &input; }
    static uint8_t* output_register() { return &output; }

    static void reset();

    static uint8_t mode;
    static uint8_t input;
    static uint8_t output;

    constexpr port() {}
};

using P0_ = port<0>;
using P1_ = port<1>;
using P2_ = port<2>;

constexpr port<0> P0;
constexpr port<1> P1;
constexpr port<2> P2;

// Means we can't include this in more than one cpp file in same test program.
template <int I>
uint8_t port<I>::mode = 0;

template <int I>
uint8_t port<I>::input = 0;

template <int I>
uint8_t port<I>::output = 0;

}}}

#endif
