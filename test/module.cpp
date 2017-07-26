#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE module
#include <boost/test/unit_test.hpp>

#include "../include/hardware/arch/generic/module.hpp"

#include "../include/mpl/util.hpp"
#include "../include/mpl/integral_constant.hpp"

using namespace crazy_arduino::hardware::arch::generic;

struct test_module0 : module<test_module0,2>
{
    constexpr test_module0() {}
};

struct test_module1 : module<test_module1,1>
{
    constexpr test_module1() {}
};

BOOST_AUTO_TEST_CASE(function_creation)
{
    constexpr auto tm0 = test_module0{};
    constexpr auto f0 = tm0[0]['c'];

    BOOST_CHECK(mpl::same_type(f0, function<test_module0,int,char>{}));
}

struct visitor
{
    constexpr visitor() {}

    template < typename ... Addr >
    constexpr auto operator()(function<test_module0, Addr...>) const { return 0_c; }

    template < typename ... Addr >
    constexpr auto operator()(function<test_module1,Addr...>) const { return 1_c; }
};

BOOST_AUTO_TEST_CASE(module_match)
{

    constexpr auto tm0 = test_module0{};
    constexpr auto tm1 = test_module1{};
    constexpr auto v = visitor{};

    BOOST_CHECK(mpl::same_type(v(tm0[0]['c']), 0_c));
    BOOST_CHECK(mpl::same_type(v(tm1[2]), 1_c));
}
