#ifndef AVR_HARDWARE_PINS_HPP
#define AVR_HARDWARE_PINS_HPP

namespace avr { namespace hardware { namespace pins {

constexpr int PA = 1;
constexpr int PB = 2;
constexpr int PC = 3;
constexpr int PD = 4;



// On the Arduino board, digital pins are also used
// for the analog output (software PWM).  Analog input
// pins are a separate set.

// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+
//
// (PWM+ indicates the additional PWM pins on the ATmega168.)

// ATMEL ATMEGA1280 / ARDUINO
//
// 0-7 PE0-PE7   works
// 8-13 PB0-PB5  works
// 14-21 PA0-PA7 works
// 22-29 PH0-PH7 works
// 30-35 PG5-PG0 works
// 36-43 PC7-PC0 works
// 44-51 PJ7-PJ0 works
// 52-59 PL7-PL0 works
// 60-67 PD7-PD0 works
// A0-A7 PF0-PF7
// A8-A15 PK0-PK7


constexpr uint8_t digital_pin_to_port[] = {
    PD, /* 0 */
    PD,
    PD,
    PD,
    PD,
    PD,
    PD,
    PD,
    PB, /* 8 */
    PB,
    PB,
    PB,
    PB,
    PB,
    PC, /* 14 */
    PC,
    PC,
    PC,
    PC,
    PC,
};
#undef digitalPinToPort
constexpr uint8_t digitalPinToPort(uint8_t pin)
{
    return digital_pin_to_port[pin];
}
template < typename Pin >
constexpr uint8_t port(Pin)
{
    return digitalPinToPort(Pin::id);
}


// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
constexpr uint16_t port_to_mode[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &DDRB,
    (uint16_t) &DDRC,
    (uint16_t) &DDRD,
};
#undef portModeRegister
constexpr uint16_t portModeRegister(uint8_t port)
{
    return port_to_mode[port];
}
template < typename Pin >
constexpr uint16_t mode_register(Pin pin)
{
    return portModeRegister(port(pin));
}

constexpr uint16_t port_to_output[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &PORTB,
    (uint16_t) &PORTC,
    (uint16_t) &PORTD,
};
#undef portOutputRegister
constexpr uint16_t portOutputRegister(uint8_t port)
{
    return port_to_output[port];
}
template < typename Pin >
constexpr uint16_t output_register(Pin pin)
{
    return portOutputRegister(port(pin));
}

constexpr uint16_t port_to_input[] = {
    NOT_A_PORT,
    NOT_A_PORT,
    (uint16_t) &PINB,
    (uint16_t) &PINC,
    (uint16_t) &PIND,
};
#undef portInputRegister
constexpr uint16_t portInputRegister(uint8_t port)
{
    return port_to_input[port];
}
template < typename Pin >
constexpr uint16_t input_register(Pin pin) { return portInputRegister(port(pin)); }


constexpr uint8_t digital_pin_to_bit_mask[] = {
    _BV(0), /* 0, port D */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
    _BV(6),
    _BV(7),
    _BV(0), /* 8, port B */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
    _BV(0), /* 14, port C */
    _BV(1),
    _BV(2),
    _BV(3),
    _BV(4),
    _BV(5),
};
#undef digitalPinToBitMask
constexpr uint8_t digitalPinToBitMask(uint8_t pin)
{
    return digital_pin_to_bit_mask[pin];
}
template < typename Pin >
constexpr uint8_t mask(Pin) { return digitalPinToBitMask(Pin::id); }

constexpr uint8_t digital_pin_to_timer[] = {
    NOT_ON_TIMER, /* 0 - port D */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    // on the ATmega168, digital pin 3 has hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
#else
    TIMER2B,
#endif
    NOT_ON_TIMER,
    // on the ATmega168, digital pins 5 and 6 have hardware pwm
#if defined(__AVR_ATmega8__)
    NOT_ON_TIMER,
    NOT_ON_TIMER,
#else
    TIMER0B,
    TIMER0A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 8 - port B */
    TIMER1A,
    TIMER1B,
#if defined(__AVR_ATmega8__)
    TIMER2,
#else
    TIMER2A,
#endif
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER, /* 14 - port C */
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
    NOT_ON_TIMER,
};

}}} // avr::hardware::pins

#endif
