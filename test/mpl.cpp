#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mpl
#include <boost/test/unit_test.hpp>

#include "../include/mpl/util.hpp"
#include "../include/mpl/collection.hpp"

namespace {

template < int I > struct key { constexpr key(){} };

}

BOOST_AUTO_TEST_CASE(same_type)
{
    constexpr auto t0 = mpl::same_type(0,1);
    constexpr auto t1 = mpl::same_type(0,1.);

    BOOST_CHECK(t0);
    BOOST_CHECK(!t1);
}



BOOST_AUTO_TEST_CASE(lookup_collection)
{
    constexpr auto test_collection = mpl::lookup_collection{};
    constexpr auto t0 = test_collection.add(key<0>{}, 5).add(key<1>{}, 6.66);
    constexpr auto t1 = t0[key<0>{}];
    constexpr auto t2 = t0[key<1>{}];

    static_assert(t0.has(key<0>{}),"");
    static_assert(t0.has(key<1>{}),"");
    static_assert(!t0.has(key<2>{}),"");

    BOOST_CHECK_EQUAL(t1, 5);
    BOOST_CHECK_EQUAL(static_cast<int>(t2 * 100 + .5), 666);
}
