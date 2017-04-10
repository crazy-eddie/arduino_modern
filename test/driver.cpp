#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE driver
#include <boost/test/unit_test.hpp>

#include "../include/avr/hardware/test/arch.hpp"
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/tags.hpp"
#include "../include/avr/hardware/initialize.hpp"

using namespace avr;
using namespace avr::hardware;
using namespace avr::hardware::test;
using namespace avr::hardware::pin_config;

BOOST_AUTO_TEST_CASE(pass) {  }


BOOST_AUTO_TEST_CASE(pin_io)
{
    auto const driver = initialize(test_arch.set_mode(pin1,output)
                                            .set_mode(pin2,output)
                                            .set_mode(pin3,input));

    driver.high(pin1);
    BOOST_CHECK_EQUAL(0x01, P0.output);
    driver.high(pin2);
    BOOST_CHECK_EQUAL(0x03, P0.output);
    driver.low(pin1);
    BOOST_CHECK_EQUAL(0x02, P0.output);

    P1.input = 0x01;
    BOOST_CHECK(driver.read(pin3));
}

BOOST_AUTO_TEST_CASE(multi_pin)
{
    auto const driver = initialize(test_arch.set_mode(pin1,output)
                                            .set_mode(pin2,output)
                                            .set_mode(pin3,output));

    P0.output = 0;
    P1.output = 0;

    driver.high(pin1, pin2, pin3);
    BOOST_CHECK_EQUAL(0x03, P0.output);
    BOOST_CHECK_EQUAL(0x01, P1.output);

    driver.low(pin1,pin3);
    BOOST_CHECK_EQUAL(0x02, P0.output);
    BOOST_CHECK_EQUAL(0x00, P1.output);

    driver.toggle(pin1,pin2);
    BOOST_CHECK_EQUAL(0x01, P0.output);
}
