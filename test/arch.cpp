#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE arch
#include <boost/test/unit_test.hpp>

#include "../include/avr/hardware/test/arch.hpp"
#include "../include/mpl/integral_constant.hpp"
#include "../include/avr/hardware/tags.hpp"

#include "../include/avr/hardware/pin.hpp"


BOOST_AUTO_TEST_CASE(pass) {  }

BOOST_AUTO_TEST_CASE(immediate_interface)
{
    constexpr auto p1 = avr::hardware::pin(avr::hardware::test::P0, 0x01);
    constexpr auto p2 = avr::hardware::pin(avr::hardware::test::P0, 0x02);

    constexpr auto ops = avr::hardware::basic_ops<avr::hardware::test::test_arch_>{};

    ops.set_mode(p1, avr::hardware::pin_config::output);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 1);

    ops.set_mode(p2, avr::hardware::pin_config::output);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 3);

    ops.high(p1);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.output, 1);

    ops.set_mode(p1, avr::hardware::pin_config::input);

    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 2);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.output, 0);

    avr::hardware::test::P0.input = 5;
    BOOST_CHECK(ops.read(p1));
}

BOOST_AUTO_TEST_CASE(pin_registration)
{
    // TODO: Something about the initial call should specify what kind of mask is expected.
    constexpr auto hardware =
            avr::hardware::arch_<avr::hardware::test::test_arch_>{}
                .register_pin(avr::pin1, avr::hardware::test::P0, 0)
                .register_pin(avr::pin2, avr::hardware::test::P0, 1)
                .register_pin(avr::pin3, avr::hardware::test::P1, 0)
            ;

    constexpr auto t0 = hardware.has_pin(avr::pin1);
    constexpr auto t1 = hardware.has_pin(avr::pin2);
    constexpr auto t2 = hardware.has_pin(avr::pin3);
    constexpr auto t3 = hardware.has_pin(avr::pin4);

    constexpr auto hardware2 = hardware.register_pin(avr::pin4, avr::hardware::test::P1, 1);
    constexpr auto t4 = hardware2.has_pin(avr::pin4);

    BOOST_CHECK(t0 && t1 && t2 && !t3 && t4);
}
