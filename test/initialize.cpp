#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE configurator
#include <boost/test/unit_test.hpp>


#include "../include/avr/hardware/configurator.hpp"
#include "../include/avr/hardware/test/arch.hpp"
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/tags.hpp"
#include "../include/avr/hardware/initialize.hpp"

using namespace avr::hardware;
using namespace avr::hardware::test;
using namespace avr::hardware::pin_config;

using namespace avr;

BOOST_AUTO_TEST_CASE(initializes)
{
    auto const driver = initialize(test_arch.set_mode(pin1,input)
                                            .set_mode(pin2,output)
                                            .set_mode(pin3,input));

    BOOST_CHECK_EQUAL(0x02, P0.mode);
    BOOST_CHECK_EQUAL(0x00, P1.mode);
}
