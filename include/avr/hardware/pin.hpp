#ifndef AVR_HARDWARE_PIN_HPP
#define AVR_HARDWARE_PIN_HPP

#include "../../mpl/collection.hpp"

namespace avr { namespace hardware {

namespace detail_ {

template < typename Port, typename Mask >
struct pin
{
    using register_type = typename Port::register_type;
    constexpr pin() {}

    static constexpr Port port() { return Port{}; }
    static constexpr register_type mask() { return Mask::value(); }
};

}

template < typename Port, typename Mask >
constexpr detail_::pin<Port,Mask> pin(Port, Mask)
{
    return detail_::pin<Port, Mask>{};
}


namespace detail_ {

struct pin_collator
{
    constexpr pin_collator() {}

    template < typename Result, typename Port, typename Mask >
    constexpr auto operator()(Result result, pin<Port,Mask> pin) const
    {
        constexpr auto pin_collection = result.at(pin.port(), mpl::integral_constant<int,0>{});
        return result.insert(pin.port(), pin_collection | Mask{});
    }
};

template < typename PinCollection >
struct lookup_pin
{
    constexpr lookup_pin(){}

    template < typename Result, typename Pin >
    constexpr auto operator()(Result result, Pin pin) const
    {
        return result.append(PinCollection::get(pin));
    }
};

}

template < typename PinCollection, typename ... Pin >
constexpr auto collate_pins(PinCollection pin_collection, Pin ... pin)
{
    constexpr auto pin_pack = mpl::collect_pack(pin...);
    constexpr auto transformed_pack = mpl::accumulate(pin_pack, mpl::collection{}, detail_::lookup_pin<PinCollection>{});

    return mpl::accumulate(transformed_pack, mpl::lookup_collection{}, detail_::pin_collator{});
}



}}

#endif
