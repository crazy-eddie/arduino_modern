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

constexpr auto test_platform =
    avr::hardware::arch_<avr::hardware::test::test_arch_>{}
        .register_pin(avr::pin1, avr::hardware::test::P0, 0)
        .register_pin(avr::pin2, avr::hardware::test::P0, 1)
        .register_pin(avr::pin3, avr::hardware::test::P1, 0)
    ;


BOOST_AUTO_TEST_CASE(initial_state)
{
    constexpr auto test_configurator = avr::hardware::describe_platform(test_platform);

    constexpr auto t0 = test_configurator.available(avr::pin1);
    constexpr auto t1 = test_configurator.available(avr::pin2);
    constexpr auto t2 = test_configurator.available(avr::pin3);

    BOOST_CHECK(t0 && t1 && t2);
}

#if 1
BOOST_AUTO_TEST_CASE(configure_pins)
{
    constexpr auto test_configurator = avr::hardware::describe_platform(test_platform);

    constexpr auto configured =
        test_configurator
            .set_mode(avr::pin1, avr::hardware::pin_config::input)
            .set_mode(avr::pin2, avr::hardware::pin_config::output)
            // uncomment next line to cause blowout.
            //.set_mode(avr::pin1, avr::hardware::pin_config::output) // TODO: devise a way for a better error message here.
        ;

    // pin availability:
    constexpr auto av0 = configured.available(avr::pin1);
    constexpr auto av1 = configured.available(avr::pin2);
    constexpr auto av2 = configured.available(avr::pin3);

    BOOST_CHECK(!av0 && !av1 && av2);

    // get modes:
    constexpr auto m0 = configured.mode(avr::pin1);
    constexpr auto m1 = configured.mode(avr::pin2);

    BOOST_CHECK(mpl::same_type(m0, avr::hardware::pin_config::input));
    BOOST_CHECK(mpl::same_type(m1, avr::hardware::pin_config::output));

    // uncomment to explode:
    //constexpr auto blow = configured.mode(avr::pin3);
}
#endif

#if 0
namespace {

struct test_device
{
    //template < typename Configurator >
    //static constexpr auto configure_pin(Configurator config)
    //    -> decltype(config.set_mode(pin1, input).set_mode(pin2,output).set_mode(pin3,output))
    //{
    //    return config.set_mode(pin1, input).set_mode(pin2,output).set_mode(pin3,output);
    //}
    constexpr test_device(){}

    template < typename Configurator >
    static constexpr auto configure(Configurator config)
    {
        return config.create_config(config.pins, config.devices.add(test_device{}))
                .set_mode(pin1,input).set_mode(pin2,output).set_mode(pin3,output);
    }
};


BOOST_AUTO_TEST_CASE(devices) // TODO: This should actually remove the pin entirely.  Don't want it to give access later.
{
    constexpr auto test_configurator = configurator<int, test_desc<pin1_tag>, test_desc<pin2_tag>, test_desc<pin3_tag>>{};

    constexpr auto test0 = test_configurator.add_device(test_device{});
    //constexpr auto test0 = test_configurator;

    // assert that the device was added and pins set up to the appropriate mode.
    BOOST_CHECK(is_same(input, pin_mode(test0,pin1)));
    BOOST_CHECK(is_same(output, pin_mode(test0,pin2)));
    BOOST_CHECK(is_same(output, pin_mode(test0,pin3)));

    BOOST_CHECK(has_device(test0, test_device{}));
}
#endif
