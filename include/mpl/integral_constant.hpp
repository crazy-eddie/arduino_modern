#ifndef MPL_INTEGRAL_CONSTANT_HPP
#define MPL_INTEGRAL_CONSTANT_HPP

namespace mpl {

template < typename T, T Value >
struct integral_constant
{
    constexpr static T value = Value;
};

template < uint8_t Value >
using uint8_t_ = integral_constant<uint8_t, Value>;

}


#endif
