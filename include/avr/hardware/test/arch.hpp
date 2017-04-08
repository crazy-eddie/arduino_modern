#ifndef AVR_HARDWARE_TEST_HPP
#define AVR_HARDWARE_TEST_HPP

#include "../configurator.hpp" // TODO: Shouldn't be depending on this in this file.
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


constexpr auto test_arch =
    describe_platform(arch_<test_arch_>{}
        .register_pin(pin1, P0, 1)
        .register_pin(pin2, P0, 2)
        .register_pin(pin3, P1, 1)
    );

}}}



#endif
