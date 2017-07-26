#ifndef HARDWARE_ARCH_GENERIC_PIN_HPP
#define HARDWARE_ARCH_GENERIC_PIN_HPP

#include "../../../mpl/integral_constant.hpp"

namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

template < int Idx >
struct pin
{
    constexpr pin() {}
};

template < char ... Seq >
constexpr auto operator""_p()
{
    return pin<operator""_c<Seq...>().value()>{};
}

template < typename L, typename R >
struct pin_pair
{
    constexpr pin_pair() {}

    using left = L;
    using right = R;
};

template < int L, int R >
constexpr auto operator , (pin<L>,pin<R>) { return pin_pair<pin<L>,pin<R>>{}; }

}}}}

#endif
