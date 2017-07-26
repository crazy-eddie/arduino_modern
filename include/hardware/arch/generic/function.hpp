#ifndef HARDWARE_ARCH_GENERIC_FUNCTION_HPP
#define HARDWARE_ARCH_GENERIC_FUNCTION_HPP

#include "../../../mpl/collection.hpp"
#include "../../../mpl/undefined.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

template < typename F1, typename Idx, typename Collection = mpl::lookup_collection >
struct chip_builder;

template < typename ... Functions >
struct function_set
{
    constexpr function_set() {}

    constexpr chip_builder<function_set, mpl::undefined> operator -- (int) const { return chip_builder<function_set, mpl::undefined>{}; }
};


template < typename ... Address >
struct function : function_set<function<Address...>>
{
    constexpr function() {}
};

template < typename ... F1, typename ... F2 >
constexpr auto operator | (function_set<F1...>,function_set<F2...>)
{
    return function_set<F1...,F2...>{};
}

}}}}


#endif
