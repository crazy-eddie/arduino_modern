#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE configurator
#include <boost/test/unit_test.hpp>

#include "../include/avr/hardware/configurator.hpp"
#include "../include/avr/hardware/test/arch.hpp"
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/tags.hpp"

using namespace avr::hardware;
using namespace avr::hardware::test;
using namespace avr::hardware::pin_config;

using namespace avr;

template < typename PinTag >
struct test_desc { using pin_t = PinTag; };

template < typename T0, typename T1 >
constexpr bool is_same(T0,T1) { return false; }
template < typename T >
constexpr bool is_same(T,T) { return true; }



BOOST_AUTO_TEST_CASE(set_mode)
{
    constexpr auto test_configurator = configurator<void, test_desc<pin1_tag>, test_desc<pin2_tag>>{};

    constexpr auto test0 = test_configurator.set_mode(pin1, input);
    //constexpr auto test1 = test0.set_mode(pin1, output); // compile error!
    constexpr auto test2 = test0.set_mode(pin2, output);

    static_assert(is_same(test_configurator, configurator_<void, pin_config_<test_desc<pin1_tag>, unset_mode>, pin_config_<test_desc<pin2_tag>, unset_mode> >{}), "");

    static_assert(is_same(test0, configurator_<void,  pin_config_<test_desc<pin1_tag>, input_tag>, pin_config_<test_desc<pin2_tag>, unset_mode> >{}), "");
    //static_assert(is_same(test1, configurator_< pin_config_<test_desc<pin1_tag>, input_tag>, pin_config_<test_desc<pin2_tag>, unset_mode> >{}), "");
    static_assert(is_same(test2, configurator_<void, pin_config_<test_desc<pin1_tag>, input_tag>, pin_config_<test_desc<pin2_tag>, output_tag> >{}), "");

}
