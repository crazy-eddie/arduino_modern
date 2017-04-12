
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/standard/arch.hpp"
#include "../include/avr/hardware/standard/ports.hpp"
#include "../include/avr/hardware/initialize.hpp"

#include <util/delay.h>

using namespace avr::hardware::standard;
using namespace avr::hardware;

using namespace avr;

// 1260 16 12 1288 before using the driver.
auto const driver = initialize(standard_hw.set_mode(pin13, pin_config::output));
                                          //.set_mode(pin1, pin_config::output)
                                          //.set_mode(pin2, pin_config::output));

// 666 0 9 675 == same as not doing anything but delay.  The constexpr stuff is functioning.
//constexpr auto blah = standard_hw.set_mode(pin13, pin_config::output);

void setup()
{
}

void loop() {
    driver.high(pin13);
    _delay_ms(1000);
    driver.low(pin13);
    _delay_ms(500);
}

int main()
{
    while (1) { loop(); }
}


/*
 *
 * original:
text       data     bss     dec     hex filename
   1064       0       9    1073     431 /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep
 *
 * set_mode:
text       data     bss     dec     hex filename
    934       0       9     943     3af /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep
 *
 * high/low:
text       data     bss     dec     hex filename
    690       0       9     699     2bb /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep

 * initialize:
text       data     bss     dec     hex filename
    728       0       9     737     2e1 /home/satan/github/arduino_modern/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino_modern/platform/platform_test/standard.eep
 *
 * no more core:
text       data     bss     dec     hex filename
    238       0       0     238      ee /home/satan/github/arduino_modern/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino_modern/platform/platform_test/standard.eep

 */
