#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE pins
#include <boost/test/unit_test.hpp>

#include "../include/avr/stepper.hpp"
#include "../include/avr/hardware/test/arch.hpp"
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/initialize.hpp"

constexpr auto test = avr::gear_train<1,64>::ratio;

BOOST_AUTO_TEST_CASE(empty) { }

BOOST_AUTO_TEST_CASE(motor_config)
{
}

BOOST_AUTO_TEST_CASE(motor_driver)
{
}
