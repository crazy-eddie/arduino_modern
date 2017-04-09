#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mpl
#include <boost/test/unit_test.hpp>

#include "../include/mpl/util.hpp"
#include "../include/mpl/collection.hpp"
#include "../include/mpl/integral_constant.hpp"

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

BOOST_AUTO_TEST_CASE(integral)
{
    BOOST_CHECK_EQUAL(5, (mpl::detail_::create_constant<int, '5'>::value()));

    constexpr auto val = 5_c;
    BOOST_CHECK_EQUAL(5, val.value());
}


namespace {

template < typename End >
constexpr int count(End,End) { return 0; }

template < typename Beg, typename End >
constexpr int count(Beg iter, End end)
{
    return 1 + count(iter.next(), end);
}

}

BOOST_AUTO_TEST_CASE(lookup_collection)
{
    constexpr auto test_collection = mpl::lookup_collection{};
    constexpr auto t0 = test_collection.insert(key<0>{}, 5_c).insert(key<1>{}, 666_c);
    constexpr auto t1 = t0.get(key<0>{});
    constexpr auto t2 = t0.get(key<1>{});
    constexpr auto t3 = count(t0.begin(), t0.end());

    constexpr auto t4 = t0.insert(key<0>{}, 9_c);

    static_assert(t0.has(key<0>{}),"");
    static_assert(t0.has(key<1>{}),"");
    static_assert(!t0.has(key<2>{}),"");

    //BOOST_CHECK_EQUAL(t3, 2);

    BOOST_CHECK_EQUAL(t4.get(key<0>{}).value(), 9);

    BOOST_CHECK_EQUAL(t1.value(), 5);
    BOOST_CHECK_EQUAL(t2.value(), 666);


    constexpr auto test_collection2 = t0.remove(key<0>{});
    BOOST_CHECK(!test_collection.has(key<0>{}));

    // uncomment to explode...
    //constexpr auto blow = test_collection2[key<0>{}];
}
