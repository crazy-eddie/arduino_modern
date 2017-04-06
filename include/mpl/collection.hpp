#ifndef MPL_COLLECTION_HPP
#define MPL_COLLECTION_HPP

#include "integral_constant.hpp"
#include "util.hpp"

namespace mpl {

template < typename ... Pack >
struct collection;

template < >
struct collection<>
{
    constexpr collection(){}
};

template < typename Head, typename ... Tail >
struct collection<Head,Tail...> : collection<Tail...>
{
    constexpr collection() : collection<Tail...>{} {}
    constexpr collection(Head h, Tail ... tail) : head(h), collection<Tail...>{tail...} {}

    template < int I >
    constexpr auto operator[](integral_constant<int,I>) -> decltype(collection<Tail...>::operator[](declval<integral_constant<int,I-1>()))
    {
        return collection<Tail...>::operator[](integral_constant<int,I-1>{});
    }

    constexpr Head operator[](integral_constant<int,0>) { return head; }


private:
    Head head;
};


}


#endif
