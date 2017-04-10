#ifndef MPL_COLLECTION_HPP
#define MPL_COLLECTION_HPP

#include "integral_constant.hpp"
#include "util.hpp"

namespace mpl {

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

    template < typename Key_, typename Def >
    static constexpr auto at(Key_ key, Def def) { return Next::at(key,def); }

    template < typename Def >
    static constexpr auto at(Key, Def) { return Value{}; }

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

    template < typename Key, typename Def >
    static constexpr Def at(Key, Def def) { return def; }
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

    struct value_type
    {
        constexpr value_type(){}

        static constexpr Key key() { return Key{}; }
        static constexpr Value value() { return Value{}; }
    };

    static constexpr auto deref()
    {
        return value_type{};
    }

    static constexpr Key key() { return Key{}; }

    static constexpr lc_iter<Next> next() { return lc_iter<Next>{}; }
};

template < typename Key, typename Value, typename Next >
constexpr lc_iter<lc_term> lc_node<Key,Value,Next>::end() { return lc_iter<lc_term>{}; }

}

struct lookup_collection : detail_::lc_term
{
    constexpr lookup_collection(){}
};


namespace detail_ {

struct c_term;

template < typename Value, typename Next = c_term >
struct c_node
{
    template < typename Value_ >
    static constexpr auto append(Value_ val)
    {
        using next = decltype(Next::append(val));
        return c_node<Value,next>{};
    }

    template < typename Idx >
    static constexpr auto get(Idx idx)
    {
        return Next::get(idx - 1_c);
    }

    static constexpr Value get(mpl::integral_constant<int,0>)
    {
        return Value{};
    }

    static constexpr auto begin();
    static constexpr auto end();
};

struct c_term
{
    template < typename Value_ >
    static constexpr auto append(Value_)
    {
        return c_node<Value_>{};
    }
};

template < typename Collection >
struct c_iter
{
    constexpr c_iter(){}
};

template < typename Value, typename Next >
struct c_iter<c_node<Value,Next>>
{
    constexpr c_iter(){}

    static constexpr Value deref() { return Value{}; }
    static constexpr c_iter<Next> next() { return c_iter<Next>(); }
};

template < typename Value, typename Next >
constexpr auto c_node<Value,Next>::begin() { return c_iter<c_node<Value,Next>>{}; }

template < typename Value, typename Next >
constexpr auto c_node<Value,Next>::end() { return c_iter<c_term>{}; }

template < typename T >
constexpr auto collect_pack(T t)
{
    return c_term::append(t);
}

template < typename T, typename ... Pack>
constexpr auto collect_pack(T t, Pack ... pack)
{
    return collect_pack(pack...).append(t);
}

}

struct collection : detail_::c_term
{
    constexpr collection(){}
};

template < typename ... Pack >
constexpr auto collect_pack(Pack...pack)
{
    return detail_::collect_pack(pack...);
}


}


#endif
