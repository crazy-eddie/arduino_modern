#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE pins
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(empty) {}

#if 0
#include "../include/avr/digital_pin.hpp"

struct test_arch
{
    struct input_tag {} input;
    struct output_tag {} output;

    template < typename PinTag >
    constexpr input_pin<PinTag::id, test_arch> initialize(PinTag, input_tag)
    {
        return input_pin<PinTag::id, test_arch>{*this};
    }
    template < typename PinTag >
    constexpr output_pin<PinTag::id, test_arch> initialize(PinTag, output_tag)
    {
        return output_pin<PinTag::id, test_arch>{*this};
    }

    static bool read(pin_tag<1>)
    {
        return called;
    }
    static void high(pin_tag<2>) { called = true; }
    static void low(pin_tag<2>) { called = false; }

    static bool called;
};
bool test_arch::called = false;

BOOST_AUTO_TEST_CASE(basic)
{
    constexpr auto unconfigured = unconfigured_pin{};

    constexpr auto input = unconfigured.input();

    constexpr auto pin_1 = input.initialize(pin1, test_arch{});
    constexpr auto pin_2 = unconfigured.output().initialize(pin2, test_arch{});

    BOOST_CHECK_EQUAL(pin_1.read(), false);
    pin_2.high();
    BOOST_CHECK_EQUAL(pin_1.read(), true);
}
#endif
