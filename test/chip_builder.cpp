#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE chip_builder
#include <boost/test/unit_test.hpp>

#include "../include/hardware/arch/generic/chip_builder.hpp"
#include "../include/hardware/arch/generic/module.hpp"
#include "../include/hardware/arch/generic/pin.hpp"

#include "../include/mpl/util.hpp"

using namespace crazy_arduino::hardware::arch::generic;

BOOST_AUTO_TEST_CASE(blah)
{
    struct test_module : module<test_module,1> { constexpr test_module(){} };

    constexpr auto tm = test_module{};

    constexpr auto chip =*
            (tm[0_c] | tm[1_c])--[1_p - U - 6_p]--(tm[2_c] | tm[3_c])
                      (tm[4_c])--[2_p   ,   5_p]--(tm[5_c])
  (tm[6_c] | tm[7_c] | tm[8_c])--[3_p - _ - 4_p]--(tm[9_c] | tm[10_c]);

    BOOST_CHECK(mpl::same_type(chip.get(1_p), function_set<function<test_module, decltype(0_c)>, function<test_module, decltype(1_c)>>{}));
}
