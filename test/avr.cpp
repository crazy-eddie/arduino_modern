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

using namespace crazy_arduino::hardware::arch;

BOOST_AUTO_TEST_CASE(digital_ports)
{
    BOOST_CHECK(mpl::same_type(avr::digital_io[0_c][0_c], generic::function<avr::detail_::digital_io, decltype(0_c), decltype(0_c)>{}));
}


