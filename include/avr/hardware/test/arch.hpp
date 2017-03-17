#ifndef AVR_HARDWARE_TEST_HPP
#define AVR_HARDWARE_TEST_HPP

#include "../../pins.hpp"
#include "ports.hpp"
#include "../tags.hpp"
#include "../arch.hpp"

namespace avr { namespace hardware { namespace test {

struct test_arch_
{
    static bool& status_register() { static bool reg = false; return reg; }

    static void disable_interrupts() {}
    static void enable_interrupts() {}
};

constexpr arch_<test_arch_> test_arch;

}}}



#endif
