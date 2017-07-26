
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE pin
#include <boost/test/unit_test.hpp>
#include "../include/mpl/util.hpp"

#include "../include/hardware/arch/generic/pin.hpp"


using namespace crazy_arduino::hardware::arch::generic;

BOOST_AUTO_TEST_CASE(SNOTHU)
{
    constexpr auto idx = 1_p;

    BOOST_CHECK(mpl::same_type(idx, pin<1>{}));
}
