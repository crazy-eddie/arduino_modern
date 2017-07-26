#ifndef HARDWARE_ARCH_GENERIC_MODULE_HPP
#define HARDWARE_ARCH_GENERIC_MODULE_HPP

#include "function.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

namespace detail_ {

template < size_t ParamsRemain, typename ... Args >
struct function_addresser
{
    constexpr function_addresser() {}

    template < typename Tag >
    constexpr auto operator [] (Tag) const
    {
        return function_addresser<ParamsRemain - 1, Args..., Tag>{};
    }
};

template < typename ... Args >
struct function_addresser<1U, Args...>
{
    constexpr function_addresser() {}

    template < typename Tag >
    constexpr auto operator [] (Tag) const
    {
        return function<Args..., Tag>{};
    }
};

} // detail_

template < typename Module, size_t ParamCount >
struct module : detail_::function_addresser<ParamCount, Module>
{
    constexpr module() {}
};

}}}}


#endif
