#ifndef AVR_HARDWARE_STANDARD_PINS_H
#define AVR_HARDWARE_STANDARD_PINS_H

#include "../../pins.hpp"
#include "ports.hpp"

namespace avr { namespace hardware { namespace standard { namespace pins {

constexpr uint8_t register_masks[] =
{
          _BV(0),_BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
        , _BV(0),_BV(1), _BV(2), _BV(3), _BV(4), _BV(5)
        , _BV(0),_BV(1), _BV(2), _BV(3), _BV(4), _BV(5)
};

//constexpr ports::PB_ port(pin13_tag) { return PB; }

template < typename PinTag >
struct pin_port;

template < >
struct pin_port<pin8_tag> { using type = ports::PB_; };
template < >
struct pin_port<pin9_tag> { using type = ports::PB_; };
template < >
struct pin_port<pin10_tag> { using type = ports::PB_; };
template < >
struct pin_port<pin11_tag> { using type = ports::PB_; };
template < >
struct pin_port<pin12_tag> { using type = ports::PB_; };
template < >
struct pin_port<pin13_tag> { using type = ports::PB_; };

template < typename PinTag >
using port = typename pin_port<PinTag>::type;

template < typename PinTag >
constexpr ports::pin<port<PinTag>, register_masks[PinTag::id]> pin(PinTag)
{
    return ports::pin<port<PinTag>, register_masks[PinTag::id]>{};
}

//constexpr ports::pin<ports::PB_, register_masks[13]> pin(pin13_tag)
//{
//   return ports::pin<ports::PB_, register_masks[13]>{};
//}

}}}}


#endif
