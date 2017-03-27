#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE arch
#include <boost/test/unit_test.hpp>

#include "../include/avr/hardware/test/arch.hpp"
#include "../include/mpl/integral_constant.hpp"
#include "../include/avr/hardware/tags.hpp"


BOOST_AUTO_TEST_CASE(pass) {  }

using namespace avr::hardware::test;
using namespace avr::hardware::pin_config;
using namespace mpl;

BOOST_AUTO_TEST_CASE(immediate_interface)
{
    using p1_t = pin<P0_, integral_constant<uint8_t, 0x01>>;
    using p2_t = pin<P0_, integral_constant<uint8_t, 0x02>>;

    test_arch.set_mode(p1_t(), output);
    BOOST_CHECK_EQUAL(P0.mode, 1);

    test_arch.set_mode(p2_t(), output);
    BOOST_CHECK_EQUAL(P0.mode, 3);

    test_arch.high(p1_t());
    BOOST_CHECK_EQUAL(P0.output, 1);

    test_arch.set_mode(p1_t(), input);

    BOOST_CHECK_EQUAL(P0.mode, 2);
    BOOST_CHECK_EQUAL(P0.output, 0);

    P0.input = 5;
    BOOST_CHECK(test_arch.read(p1_t()));
}

BOOST_AUTO_TEST_CASE(pin_registration)
{
    constexpr auto hardware = test_arch.register_pin(avr::pin1, P0, BV(0))
                                       .register_pin(avr::pin2, P0, BV(1))
                                       .register_pin(avr::pin3, P1, BV(0));

    static_assert(hardware.has_pin(avr::pin1), "");
    static_assert(hardware.has_pin(avr::pin2), "");
    static_assert(hardware.has_pin(avr::pin3), "");

    static_assert(!hardware.has_pin(avr::pin4), "");

    constexpr auto hardware2 = hardware.register_pin(avr::pin4, P1, BV(1));
    static_assert(hardware2.has_pin(avr::pin4), "");
}

BOOST_AUTO_TEST_CASE(fin)
{
    //constexpr auto configurator = test_arch.register_pin(avr::pin1, P0, BV(0))
    //                                       .register_pin(avr::pin2, P0, BV(1))
    //                                       .register_pin(avr::pin3, P1, BV(0)).fin();
}

