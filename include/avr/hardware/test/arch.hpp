#ifndef AVR_HARDWARE_TEST_HPP
#define AVR_HARDWARE_TEST_HPP

#include "../../pins.hpp"
#include "ports.hpp"
#include "../tags.hpp"
#include "../arch.hpp"
#include "../../../mpl/integral_constant.hpp"

namespace avr { namespace hardware { namespace test {

struct test_arch_
{
    static bool& status_register() { static bool reg = false; return reg; }

    static void disable_interrupts() {}
    static void enable_interrupts() {}
};

#define BV(X) mpl::integral_constant<uint8_t, 1 << X>{}

constexpr auto test_arch =
        arch_<test_arch_>{}
            .register_pin(pin1, P0, BV(0))
            .register_pin(pin2, P0, BV(1))
            .register_pin(pin3, P1, BV(0))
        .fin();

}}}



#endif
