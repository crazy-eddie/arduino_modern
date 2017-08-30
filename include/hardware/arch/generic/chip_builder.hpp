#ifndef HARDWARE_ARCH_GENERIC_CHIP_BUILDER_HPP
#define HARDWARE_ARCH_GENERIC_CHIP_BUILDER_HPP

#include "../../../mpl/undefined.hpp"

#include "pin.hpp"
#include "chip.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

template < typename F1, typename Idx, typename Collection >
struct chip_builder
{
    constexpr chip_builder() {}

    template < typename F2 >
    constexpr auto operator () (F2) const
    {
        using L = typename Idx::left;
        using R = typename Idx::right;
        constexpr auto collect = Collection{}.insert(L{}, F1{}).insert(R{}, F2{});

        return chip_builder<mpl::undefined, mpl::undefined, decltype(collect)>{};
    }

    constexpr chip_builder operator -- (int) const { return chip_builder{}; }
};

template < typename F1, typename Collection >
struct chip_builder<F1,mpl::undefined,Collection>
{
    constexpr chip_builder() {}

    template < typename Pair >
    constexpr auto operator [] (Pair) const
    {
        return chip_builder<F1,Pair,Collection>{};
    }

    constexpr chip_builder operator -- (int) const { return chip_builder{}; }
};

template < typename Collection >
struct chip_builder<mpl::undefined, mpl::undefined, Collection>
{
    constexpr chip_builder() {}

    template < typename F1 >
    constexpr auto operator () (F1) const
    {
        return chip_builder<F1,mpl::undefined,Collection>{};
    }

    constexpr chip<Collection> operator * () const { return chip<Collection>{}; }
};

constexpr auto U = mpl::undef();
constexpr auto _ = mpl::undef();

template < typename Pin >
constexpr auto operator - (Pin, mpl::undefined)
{
    return pin_pair<Pin, mpl::undefined>{};
}

template < typename Pin1, typename Pin2 >
constexpr auto operator - (pin_pair<Pin1, mpl::undefined>,Pin2)
{
    return pin_pair<Pin1,Pin2>{};
}

}}}}


#endif
