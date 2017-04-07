#ifndef MPL_COLLECTION_HPP
#define MPL_COLLECTION_HPP

#include "integral_constant.hpp"
#include "util.hpp"

namespace mpl {

#if 0
template < typename ... Pack >
struct collection_;

template < >
struct collection_<>
{
    constexpr collection(){}
};

template < typename Head, typename ... Tail >
struct collection_<Head,Tail...> : collection_<Tail...>
{
    constexpr collection_() : collection_<Tail...>{} {}
    constexpr collection_(Head h, Tail ... tail) : head(h), collection_<Tail...>{tail...} {}

    template < int I >
    constexpr auto operator[](integral_constant<int,I>)
    {
        return collection<Tail...>_::operator[](integral_constant<int,I-1>{});
    }

    constexpr Head operator[](integral_constant<int,0>) { return head; }


private:
    Head head;
};
#endif

namespace detail_ {

struct lc_term
{
    constexpr lc_term(){}

    template < typename Key >
    constexpr bool has(Key) const { return false; }
};

template < typename Key, typename Value, typename Next = lc_term >
struct lc_node : Next
{
    constexpr lc_node(Value val, Next next)
        : Next{next}
        , value{val}
    {}

    template < typename Key_, typename Value_ >
    constexpr auto add(Key_, Value_ val) const
    {
        return lc_node<Key_,Value_,lc_node>{val,*this};
    }

    template < typename Key_>
    constexpr auto operator[](Key_ key) const
    {
        return Next::operator[](key);
    }

    constexpr Value operator[](Key) const { return value; }

    template < typename Key_ >
    constexpr bool has(Key_ key) const
    {
        return Next::has(key);
    }

    constexpr bool has(Key) const { return true; }

private:
    Value value;
};

}

struct lookup_collection
{
    constexpr lookup_collection(){}

    template < typename Key, typename Value >
    constexpr auto add(Key, Value val) const
    {
        return detail_::lc_node<Key,Value>{val, detail_::lc_term{}};
    }

    template < typename Key >
    constexpr bool has(Key) const { return false; }
};


}


#endif
