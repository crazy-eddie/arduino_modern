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


namespace {

template < typename PinTag >
struct test_desc
{
    using pin_t = PinTag;


    template < typename P >
    static constexpr bool matches_tag(P) { return false; }

    static constexpr bool matches_tag(PinTag) { return true; }
};

template < typename T0, typename T1 >
constexpr bool is_same(T0,T1) { return false; }
template < typename T >
constexpr bool is_same(T,T) { return true; }

template < typename Collection > struct splitter;

template < typename First, typename ... Remain >
struct splitter<pin_collection<First,Remain...>>
{
    using first = First;
    using remain = pin_collection<Remain...>;
};

template < typename Collection, typename Pin, bool matches = splitter<Collection>::first::pin.matches_tag(Pin{}) >
struct find_pin_t
{
    using type = typename find_pin_t<typename splitter<Collection>::remain,Pin>::type;
};

template < typename Collection, typename Pin >
struct find_pin_t<Collection,Pin,true>
{
    using type = typename splitter<Collection>::first;
};

template < typename Collection, typename Pin >
constexpr typename find_pin_t<Collection,Pin>::type find_pin(Collection col, Pin pin)
{
    using found = typename find_pin_t<Collection,Pin>::type;
    return found{};
}

template < typename Config, typename Pin >
constexpr auto pin_mode(Config cfg, Pin pin) -> decltype(find_pin(cfg.pins, pin).mode)
{
    return find_pin(cfg.pins, pin).mode;
}

}


BOOST_AUTO_TEST_CASE(set_mode)
{
    constexpr auto test_configurator = configurator<int, test_desc<pin1_tag>, test_desc<pin2_tag>>{};

    constexpr auto test0 = test_configurator.set_mode(pin1, input);
    //constexpr auto test1 = test0.set_mode(pin1, output); // compile error!
    constexpr auto test2 = test0.set_mode(pin2, output);

    BOOST_CHECK(is_same(unset_mode{}, pin_mode(test_configurator, pin1)));
    BOOST_CHECK(is_same(unset_mode{}, pin_mode(test_configurator, pin2)));

    BOOST_CHECK(is_same(input, pin_mode(test0, pin1)));
    BOOST_CHECK(is_same(unset_mode{}, pin_mode(test0, pin2)));

    BOOST_CHECK(is_same(input, pin_mode(test2, pin1)));
    BOOST_CHECK(is_same(output, pin_mode(test2, pin2)));

}

namespace {

struct test_device
{
    template < typename Configurator >
    static constexpr auto configure_pin(Configurator config)
        -> decltype(config.set_mode(pin1, input).set_mode(pin2,output).set_mode(pin3,output))
    {
        return config.set_mode(pin1, input).set_mode(pin2,output).set_mode(pin3,output);
    }
};

template < typename Config, typename Device >
constexpr bool has_device(Config,Device) { return false; }

}

BOOST_AUTO_TEST_CASE(devices)
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
