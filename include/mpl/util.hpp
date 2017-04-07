#ifndef MPL_UTIL_HPP
#define MPL_UTIL_HPP

namespace mpl {

template < typename T >
T&& declval();

template < typename T0, typename T1 >
constexpr bool same_type(T0,T1) { return false; }

template < typename T >
constexpr bool same_type(T,T) { return true; }

}

#endif
