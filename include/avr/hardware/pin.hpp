#ifndef AVR_HARDWARE_PIN_HPP
#define AVR_HARDWARE_PIN_HPP


namespace avr { namespace hardware {

namespace detail_ {

template < typename Port >
struct pin
{
    using register_type = typename Port::register_type;
    constexpr pin(register_type m) : port_(), mask_(m) {}

    constexpr Port port() const { return port_; }
    constexpr register_type mask() const { return mask_; }

private:
    Port port_;
    register_type mask_;
};

}

template < typename Port >
constexpr detail_::pin<Port> pin(Port, typename Port::register_type mask)
{
    return detail_::pin<Port>{mask};
}



}}

#endif
