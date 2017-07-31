#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE chips
#include <boost/test/unit_test.hpp>

#include "../include/hardware/chip/atmega328p.hpp"

using namespace crazy_arduino::hardware::arch::generic;

namespace {

template < typename T1, typename T2 >
constexpr bool same(T1,T2,...) { return false; }

template < typename T1, typename T2, typename ... P1, typename ... P2 >
constexpr bool same(T1,T2,function_set<P1...> t1,function_set<P2...> t2)
{
    return mpl::same_type(t1,t2);
}



template < typename T1, typename T2 >
constexpr bool is_same(T1 t1,T2 t2)
{
    return same(t1, t2, t1, t2);
}

}

BOOST_AUTO_TEST_CASE(chip_atmega328p_28m1)
{
    using namespace crazy_arduino::hardware::chip;
    using namespace crazy_arduino::hardware::arch::avr;
    //using namespace crazy_arduino::hardware::arch::generic;

    //using crazy_arduino::hardware::arch::generic::operator""_p;

    constexpr auto p01 = PC[6_c];
    constexpr auto p02 = PD[0_c];
    constexpr auto p03 = PD[1_c];
    constexpr auto p04 = PD[2_c];
    constexpr auto p05 = PD[3_c];
    constexpr auto p06 = PD[4_c];
    constexpr auto p07 = VCC;
    constexpr auto p08 = GND;
    constexpr auto p09 = PB[6_c];
    constexpr auto p10 = PB[7_c];
    constexpr auto p11 = PD[5_c];
    constexpr auto p12 = PD[6_c];
    constexpr auto p13 = PD[7_c];
    constexpr auto p14 = PB[0_c];
    constexpr auto p15 = PB[1_c];
    constexpr auto p16 = PB[2_c];
    constexpr auto p17 = PB[3_c];
    constexpr auto p18 = PB[4_c];
    constexpr auto p19 = PB[5_c];
    constexpr auto p20 = AVCC;
    constexpr auto p21 = AREF;
    constexpr auto p22 = GND;
    constexpr auto p23 = PC[0_c];
    constexpr auto p24 = PC[1_c];
    constexpr auto p25 = PC[2_c];
    constexpr auto p26 = PC[3_c];
    constexpr auto p27 = PC[4_c];
    constexpr auto p28 = PC[5_c];

    BOOST_CHECK(is_same(atmega328p_28p3.get(1_p), p01));
    BOOST_CHECK(is_same(atmega328p_28p3.get(2_p) , p02));
    BOOST_CHECK(is_same(atmega328p_28p3.get(3_p) , p03));
    BOOST_CHECK(is_same(atmega328p_28p3.get(4_p) , p04));
    BOOST_CHECK(is_same(atmega328p_28p3.get(5_p) , p05));
    BOOST_CHECK(is_same(atmega328p_28p3.get(6_p) , p06));
    BOOST_CHECK(is_same(atmega328p_28p3.get(7_p) , p07));
    BOOST_CHECK(is_same(atmega328p_28p3.get(8_p) , p08));
    BOOST_CHECK(is_same(atmega328p_28p3.get(9_p) , p09));
    BOOST_CHECK(is_same(atmega328p_28p3.get(10_p), p10));
    BOOST_CHECK(is_same(atmega328p_28p3.get(11_p), p11));
    BOOST_CHECK(is_same(atmega328p_28p3.get(12_p), p12));
    BOOST_CHECK(is_same(atmega328p_28p3.get(13_p), p13));
    BOOST_CHECK(is_same(atmega328p_28p3.get(14_p), p14));
    BOOST_CHECK(is_same(atmega328p_28p3.get(15_p), p15));
    BOOST_CHECK(is_same(atmega328p_28p3.get(16_p), p16));
    BOOST_CHECK(is_same(atmega328p_28p3.get(17_p), p17));
    BOOST_CHECK(is_same(atmega328p_28p3.get(18_p), p18));
    BOOST_CHECK(is_same(atmega328p_28p3.get(19_p), p19));
    BOOST_CHECK(is_same(atmega328p_28p3.get(20_p), p20));
    BOOST_CHECK(is_same(atmega328p_28p3.get(21_p), p21));
    BOOST_CHECK(is_same(atmega328p_28p3.get(22_p), p22));
    BOOST_CHECK(is_same(atmega328p_28p3.get(23_p), p23));
    BOOST_CHECK(is_same(atmega328p_28p3.get(24_p), p24));
    BOOST_CHECK(is_same(atmega328p_28p3.get(25_p), p25));
    BOOST_CHECK(is_same(atmega328p_28p3.get(26_p), p26));
    BOOST_CHECK(is_same(atmega328p_28p3.get(27_p), p27));
    BOOST_CHECK(is_same(atmega328p_28p3.get(28_p), p28));
}
