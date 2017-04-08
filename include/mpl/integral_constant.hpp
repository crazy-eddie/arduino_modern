#ifndef MPL_INTEGRAL_CONSTANT_HPP
#define MPL_INTEGRAL_CONSTANT_HPP

namespace mpl {

template < typename T, T Value >
struct integral_constant
{
    constexpr static T value() { return Value; }
};

template < uint8_t Value >
using uint8_t_ = integral_constant<uint8_t, Value>;

namespace detail_ {

template < typename T, char ... Seq >
struct create_constant;

template < typename T, char Head, char ... Tail >
struct create_constant<T,Head,Tail...>
{
    static constexpr T value()
    {
        constexpr T val = create_constant<T,Tail...>::value() + (Head - '0') * place();
        return val;
    }

    static constexpr T place()
    {
        T n = 1;
        for (int i = 0; i < sizeof...(Tail); ++i)
            n *= 10;
        return n;
    }
};

template < typename T >
struct create_constant<T>
{
    static constexpr T value() { return T{}; }
};


}

}

template < typename what > struct w;

template < char ... Seq >
constexpr auto operator""_c()
{
    return mpl::integral_constant<int, mpl::detail_::create_constant<int, Seq...>::value()>{};
}

#endif
