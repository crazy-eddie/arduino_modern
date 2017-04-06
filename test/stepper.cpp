#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE pins
#include <boost/test/unit_test.hpp>

#include "../include/avr/stepper.hpp"
#include "../include/avr/hardware/test/arch.hpp"
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/initialize.hpp"


namespace {

// ensure that these things work in constexpr functions...
//constexpr avr::steps steps(avr::stepper_motor motor)  { return avr::steps<motor.steps()>{}; }

template < int I >
struct blah { enum { value = I };};
}


BOOST_AUTO_TEST_CASE(empty) { }

BOOST_AUTO_TEST_CASE(initial_config) // What you'll provide for a particular motor
{
    constexpr auto test_stepper = avr::stepper(avr::steps{2048}, avr::phases{4});
    constexpr auto test_steps = blah<test_stepper.steps()>::value;
    constexpr auto test_phases = blah<test_stepper.phases()>::value;

    BOOST_CHECK_EQUAL(test_steps, 2048);
    BOOST_CHECK_EQUAL(test_phases, 4);
}

BOOST_AUTO_TEST_CASE(motor_config)
{

}

BOOST_AUTO_TEST_CASE(motor_init)
{
}

BOOST_AUTO_TEST_CASE(motor_driver)
{
}
