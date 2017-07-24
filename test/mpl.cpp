#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE mpl
#include <boost/test/unit_test.hpp>

#include "../include/mpl/util.hpp"
#include "../include/mpl/collection.hpp"
#include "../include/mpl/integral_constant.hpp"
#include "../include/mpl/undefined.hpp"

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

BOOST_AUTO_TEST_CASE(collection)
{
    constexpr auto test_collection = mpl::collection{};
    constexpr auto t0 = test_collection.append(1_c);
    constexpr auto t1 = t0.append(2_c);

    BOOST_CHECK_EQUAL(t1.get(0_c).value(), 1);
    BOOST_CHECK_EQUAL(t1.get(1_c).value(), 2);

    BOOST_CHECK_EQUAL(count(t1.begin(), t1.end()), 2);
}

/* target syntax:
 * constexpr auto harp =
 * (blah | doh) -> [derp] [herp] <- (fart | cock)
 *
 * (blah | doh) [derp]  [herp] (fart | cock)
 *
 * (blah | doh)--[derp][herp]--(fart | cock)
 *
 *
 * constexpr auto some_chip =*
 * (P[A][0] / doh)--[01_c--u--28_c]--(P[D][3])
 *       (P[A][1])--[02_c  ,  27_c]--(P[D][2])
 *
 *                       ...
 *
 *       (P[A][2])--[03_c--,--26_c]--(P[D][1])
 *
 *
 *
 *
 *
 *
 */

template < typename L, typename R >
struct assign_pair
{
    constexpr assign_pair(){}

    using left = L;
    using right = R;
};

template < typename F1 = mpl::undefined
         , typename AssignPair = mpl::undefined
         , typename Collection = mpl::lookup_collection >
struct builder;

template < typename ... Functions >
struct function_set
{
    constexpr function_set(){}

    constexpr builder<function_set,mpl::undefined,mpl::lookup_collection> operator -- (int) const
    {
        return builder<function_set,mpl::undefined,mpl::lookup_collection>{};
    }
};

// Cases:
//    first 2 undefined:
//          () - start new.
//          *  - return created
template < typename Collection >
struct builder<mpl::undefined, mpl::undefined, Collection>
{
    constexpr builder() {}

    template < typename ... F1 >
    constexpr auto operator()(function_set<F1...>) const
    {
        return builder<function_set<F1...>, mpl::undefined, Collection>{};
    }

    constexpr Collection operator*() const { return Collection{}; }
};
//
//    F1 defined:
//          [] - AssignPair
template < typename F1, typename Collection >
struct builder<F1, mpl::undefined, Collection>
{
    constexpr builder(){}

    template < typename AssignPair >
    constexpr auto operator[](AssignPair) const
    {
        return builder<F1,AssignPair,Collection>{};
    }

    constexpr builder operator -- (int) const { return builder{}; }
};
//
//    F1,AssignPair defined:
//          () - insert into collection, undefine first 2.
template < typename F1, typename AssignPair, typename Collection >
struct builder
{
    constexpr builder() {}

    template < typename ... F2 >
    constexpr auto operator()(function_set<F2...>) const
    {
        using L = typename AssignPair::left;
        using R = typename AssignPair::right;
        constexpr auto new_collection = Collection{}.insert(L{}, F1{})
                                                    .insert(R{}, function_set<F2...>{});

        return builder<mpl::undefined, mpl::undefined, decltype(new_collection)>{};
    }

    constexpr builder operator--(int) const { return builder{}; }
};


template < int I > struct some_fun : function_set< some_fun<I> > { constexpr some_fun(){} };

template < typename ... F1, typename ... F2 >
constexpr auto operator | (function_set< F1... >, function_set<F2...>)
{
    return function_set<F1...,F2...>{};
}

template < int Idx >
struct pin_idx
{
    constexpr pin_idx() {}
};

template < char ... Seq >
constexpr auto operator""_p()
{
    //return mpl::integral_constant<int, mpl::detail_::create_constant<int, Seq...>::value()>{};
    return pin_idx<mpl::detail_::create_constant<int, Seq...>::value()>{};
}

template <int I1, int I2>
constexpr auto operator , (pin_idx<I1>,pin_idx<I2>) { return assign_pair<pin_idx<I1>,pin_idx<I2>>{}; }


BOOST_AUTO_TEST_CASE(derp)
{
    constexpr auto a = some_fun<1>{};
    constexpr auto b = some_fun<2>{};
    constexpr auto c = a | b;
    constexpr auto d = (1_p , 2_p);

    constexpr auto f1 = some_fun<1>{};
    constexpr auto f2 = some_fun<2>{};
    constexpr auto f3 = some_fun<3>{};
    constexpr auto f4 = some_fun<4>{};
    constexpr auto f5 = some_fun<5>{};

    BOOST_CHECK(mpl::same_type(c, function_set< some_fun<1>,some_fun<2> >{}));
    BOOST_CHECK(mpl::same_type(1_p, pin_idx<1>{}));

    constexpr auto x =*
            (f1 | f2)--[1_p , 4_p]--(f3)
                 (f4)--[2_p , 3_p]--(f5);


    constexpr auto y = mpl::lookup_collection{}
        .insert(1_p, function_set<some_fun<1>,some_fun<2>>{})
        .insert(4_p, function_set<some_fun<3>>{})
        .insert(2_p, function_set<some_fun<4>>{})
        .insert(3_p, function_set<some_fun<5>>{});

    BOOST_CHECK(mpl::same_type(x,y));
}
