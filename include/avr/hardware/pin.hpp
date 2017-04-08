#ifndef AVR_HARDWARE_PIN_HPP
#define AVR_HARDWARE_PIN_HPP


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



}}

#endif
