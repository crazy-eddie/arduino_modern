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
    constexpr auto p1 = avr::hardware::pin(avr::hardware::test::P0, uint8_t(0x01));
    constexpr auto p2 = avr::hardware::pin(avr::hardware::test::P0, uint8_t(0x02));

    avr::hardware::arch_<avr::hardware::test::test_arch_>::set_mode(p1, avr::hardware::pin_config::output);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 1);

    avr::hardware::arch_<avr::hardware::test::test_arch_>::set_mode(p2, avr::hardware::pin_config::output);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 3);

    avr::hardware::arch_<avr::hardware::test::test_arch_>::high(p1);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.output, 1);

    avr::hardware::arch_<avr::hardware::test::test_arch_>::set_mode(p1, avr::hardware::pin_config::input);

    BOOST_CHECK_EQUAL(avr::hardware::test::P0.mode, 2);
    BOOST_CHECK_EQUAL(avr::hardware::test::P0.output, 0);

    avr::hardware::test::P0.input = 5;
    BOOST_CHECK(avr::hardware::arch_<avr::hardware::test::test_arch_>::read(p1));
}

#if 0
BOOST_AUTO_TEST_CASE(pin_registration)
{
    constexpr auto hardware = arch_<test_arch_>{}.register_pin(avr::pin1, P0, BV(0))
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
    constexpr auto configurator = arch_<test_arch_>{}.register_pin(avr::pin1, P0, BV(0))
                                                     .register_pin(avr::pin2, P0, BV(1))
                                                     .register_pin(avr::pin3, P1, BV(0)).fin();
}

#endif
