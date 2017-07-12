#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mpl
#include <boost/test/unit_test.hpp>

#include "../include/mpl/integral_constant.hpp"
#include "../include/hardware/arch/avr.hpp"
#include "../include/hardware/chip/atmega328p.hpp"

template < int Idx >
struct port
{
    constexpr port(){}
};

template < int Idx >
constexpr auto create_port()
{
    return port<Idx>{};
}


BOOST_AUTO_TEST_CASE(digital_ports)
{
    constexpr auto p = create_port<'D'>();
}
