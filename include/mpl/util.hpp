#ifndef MPL_UTIL_HPP
#define MPL_UTIL_HPP

namespace mpl {

template < typename T >
T&& declval();

template < typename T0, typename T1 >
constexpr bool same_type(T0,T1) { return false; }

template < typename T >
constexpr bool same_type(T,T) { return true; }

template < typename End, typename Fun >
void for_each(End,End,Fun){}

template < typename Beg, typename End, typename Fun >
void for_each(Beg beg, End end, Fun fun)
{
    fun(beg.deref());
    for_each(beg.next(), end, fun);
}

template < typename Collection, typename Fun >
void for_each(Collection c, Fun f)
{
    for_each(c.begin(), c.end(), f);
}

template < typename End, typename Result, typename Op >
constexpr Result accumulate(End,End,Result, Op)
{
    return Result{};
}

template < typename Beg, typename End, typename Result, typename Op >
constexpr auto accumulate(Beg beg, End end, Result result, Op op)
{
    return accumulate(beg.next(), end, op(result, beg.deref()), op);
}

template < typename Collection, typename Result, typename Op >
constexpr auto accumulate(Collection collection, Result result, Op op)
{
    return accumulate(collection.begin(), collection.end(), result, op);
}

}

#endif
