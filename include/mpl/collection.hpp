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

struct lc_term;

template < typename Collection >
struct lc_iter;


template < typename Key, typename Value, typename Next = lc_term >
struct lc_node : Next
{
    constexpr lc_node(){}

    template < typename Key_ >
    static constexpr auto remove(Key_ key)
    {
        using next_ = decltype(Next::remove(key));
        return lc_node<Key, Value, next_>{};
    }

    static constexpr Next remove(Key)
    {
        return Next{};
    }

    template < typename Key_, typename Value_ >
    static constexpr auto insert(Key_ key, Value_ value)
    {
        using next = decltype(Next::insert(key,value));
        return lc_node<Key,Value, next>{};
    }

    template < typename Value_ >
    static constexpr auto insert(Key, Value_)
    {
        return lc_node<Key,Value_,Next>{};
    }

    template < typename Key_>
    static constexpr auto get(Key_ key)
    {
        return Next::get(key);
    }

    static constexpr Value get(Key) { return Value{}; }

    template < typename Key_ >
    static constexpr bool has(Key_ key)
    {
        return Next::has(key);
    }

    static constexpr bool has(Key) { return true; }

    static constexpr lc_iter<lc_node> begin()
    {
        return lc_iter<lc_node>{};
    }

    static constexpr lc_iter<lc_term> end(); // { return lc_iter<lc_term>{}; }

};

struct lc_term
{
    constexpr lc_term(){}

    template < typename Key >
    static constexpr bool has(Key) { return false; }

    template < typename Key, typename Value >
    static constexpr auto insert(Key,Value)
    {
        return lc_node<Key,Value>{};
    }
};
template < >
struct lc_iter<lc_term>
{
    constexpr lc_iter() {}
    static constexpr bool at_end() { return true; }
};


template < typename Key, typename Value, typename Next >
struct lc_iter<lc_node<Key,Value,Next>>
{
    constexpr lc_iter()
    {}

    static constexpr bool at_end() { return false; }

    static constexpr auto deref() // TODO: fix this concept!
    {
        return lc_node<Key,Value,Next>::get(key());
    }

    static constexpr Key key() { return Key{}; }

    constexpr lc_iter<Next> next() const { return lc_iter<Next>{}; }
};

template < typename Key, typename Value, typename Next >
constexpr lc_iter<lc_term> lc_node<Key,Value,Next>::end() { return lc_iter<lc_term>{}; }

}

struct lookup_collection : detail_::lc_term
{
    constexpr lookup_collection(){}
};


}


#endif
