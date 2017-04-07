#ifndef AVR_HARDWARE_PIN_HPP
#define AVR_HARDWARE_PIN_HPP


namespace avr { namespace hardware {

namespace detail_ {

template < typename Port, typename Mask = uint8_t >
struct pin
{
    constexpr pin(Mask m) : port_(), mask_(m) {}

    constexpr Port port() const { return port_; }
    constexpr Mask mask() const { return mask_; }

private:
    Port port_;
    Mask mask_;
};

}

template < typename Port, typename Mask >
constexpr detail_::pin<Port,Mask> pin(Port, Mask mask)
{
    return detail_::pin<Port,Mask>{mask};
}



}}

#endif
