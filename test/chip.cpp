#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE chip
#include <boost/test/unit_test.hpp>

#include "../include/hardware/arch/generic/chip.hpp"
#include "../include/hardware/chip/atmega328p.hpp"
#include "../include/mpl/util.hpp"

using namespace crazy_arduino::hardware::chip;
using namespace crazy_arduino::hardware::arch::avr;
using namespace mpl;

template < typename T > void f(T);

template < typename ... T > constexpr auto set(function_set<T...> f) { return f; }

BOOST_AUTO_TEST_CASE(pin_boards)
{
    constexpr auto pinned =*
            atmega328p_28p3
                .map_pin(2_p, 3_p)
                .map_pin(1_p, 2_p)
            ;

    //f(set(pinned.get(2_p)));


    static_assert(same_type(pinned.get(2_p), set(PC[6_c])), "fail");
    static_assert(same_type(pinned.get(3_p), set(PD[0_c])), "fail");
}
