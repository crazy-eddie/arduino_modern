#ifndef AVR_PINS_HPP
#define AVR_PINS_HPP

//#include <Arduino.h>
//#include <cstdint>

using uint8_t = char unsigned;

namespace avr {

template < uint8_t PinId >
struct pin_tag { static constexpr uint8_t id = PinId; constexpr pin_tag() {}};

#define PIN(X) \
    using pin ## X ## _tag = pin_tag<X>; \
    constexpr pin ## X ## _tag pin ## X

PIN(1);
PIN(2);
PIN(3);
PIN(4);
PIN(5);
PIN(6);
PIN(7);
PIN(8);
PIN(9);
PIN(10);
PIN(11);
PIN(12);
PIN(13);

}

#endif
