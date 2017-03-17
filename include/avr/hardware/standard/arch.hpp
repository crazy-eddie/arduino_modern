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
