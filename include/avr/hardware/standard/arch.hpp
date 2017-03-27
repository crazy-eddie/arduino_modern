#ifndef AVR_HARDWARE_STANDARD_ARCH_HPP
#define AVR_HARDWARE_STANDARD_ARCH_HPP

#include <Arduino.h>

#include "../tags.hpp"
#include "../arch.hpp"
#include "../../../mpl/integral_constant.hpp"

#include "ports.hpp"

namespace avr { namespace hardware { namespace standard {


struct arduino
{
    //static decltype(SREG) current_status_register() { return SREG; }
    // Not sure why, but the following adds considerable size when used.  The above doesn't.
   //static void restore_status_register(decltype(SREG) volatile& old) { SREG = old; }


    static decltype(SREG) volatile & status_register() { return SREG; }

    static void disable_interrupts() { cli(); }
    static void enable_interrupts() { sei(); }
};

using standard_arch = arch_<arduino>;


#define BV(X) mpl::integral_constant<uint8_t, 1 << X>{}

// PWM and AI pins not yet available.

constexpr auto standard =
        standard_arch{}
            .register_pin(pin1, ports::PD, BV(1))
            .register_pin(pin2, ports::PD, BV(2))
            //.register_pin(pin3, ports::PD, BV(3))
            .register_pin(pin4, ports::PD, BV(4))
            //.register_pin(pin5, ports::PD, BV(5))
            //.register_pin(pin6, ports::PD, BV(6))
            .register_pin(pin7, ports::PD, BV(7))
            .register_pin(pin8, ports::PB, BV(0))
            //.register_pin(pin9, ports::PB, BV(1))
            //.register_pin(pin10, ports::PB, BV(2))
            //.register_pin(pin11, ports::PB, BV(3))
            .register_pin(pin12, ports::PB, BV(4))
            .register_pin(pin13, ports::PB, BV(5))
        //.fin();
        ;

/*
 * constexpr auto standard = arch.register_pin(pin13, PB, i<_BV(5)>{});
 * constexpr auto pgm_hardware_initializer = standard.set_mode(pin13, output);
 *
 * auto const pgm_hardware = pgm_hardware_initializer.init();
 *
 * auto const pin = pgm_hardware.pin(pin13);
 * pin.high();
 */

}}} // avr::hardware::standard


#endif
