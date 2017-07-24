#ifndef HARDWARE_CHIP_ATMEGA328P_HPP
#define HARDWARE_CHIP_ATMEGA328P_HPP

#include "../arch/avr.hpp"

namespace crazy_arduino { namespace hardware { namespace chip {

template < int I > using ic = mpl::integral_constant<int, I>;

//constexpr auto atmega328p_28m1 = arch::avr(1_c, arch::avr.pb[0_c])
constexpr auto atmega328p_28p3 =
        arch::attach_pin(1_c, arch::PC[6_c], arch::PCINT[14_c], arch::RESET)
                 .attach_pin(2_c, arch::PD[0_c], arch::PCINT[16_c], arch::RXD[0_c])
                 .attach_pin(3_c, arch::PD[1_c], arch::PCINT[17_c], arch::TXD[0_c])
                 .attach_pin(4_c, arch::PD[2_c], arch::PCINT[18_c], arch::INT[0_c])
                 .attach_pin(5_c, arch::PD[3_c], arch::INT[1_c], arch::PCINT[19_c], arch::OC[2_c][ic<'B'>{}])
                 .attach_pin(6_c, arch::PD[4_c], arch::PCINT[20_c], arch::T[0_c], arch::XCK[0_c])
                 .attach_pin(7_c, arch::VCC)
                 .attach_pin(8_c, arch::GND)
                 .attach_pin(9_c,  arch::PB[6_c], arch::PCINT[6_c], arch::XTAL[1_c], arch::TOSC[1_c])
                 .attach_pin(10_c, arch::PB[7_c], arch::PCINT[7_c], arch::XTAL[2_c], arch::TOSC[2_c])
                 .attach_pin(11_c, arch::PD[5_c], arch::PCINT[21_c], arch::OC[0_c][ic<'B'>{}], arch::T[1_c])
                 .attach_pin(12_c, arch::PD[6_c], arch::PCINT[22_c], arch::AIN[0_c], arch::OC[0_c][ic<'A'>{}])
                 .attach_pin(13_c, arch::PD[7_c], arch::PCINT[23_c], arch::AIN[1_c])
                 .attach_pin(14_c, arch::PB[0_c], arch::PCINT[0_c], arch::CLKO, arch::ICP[1_c])

                 .attach_pin(15_c, arch::PB[1_c], arch::PCINT[1_c], arch::OC[1_c][ic<'A'>{}])
                 .attach_pin(16_c, arch::PB[2_c], arch::PCINT[2_c], arch::OC[1_c][ic<'B'>{}], arch::SS[0_c])
                 .attach_pin(17_c, arch::PB[3_c], arch::PCINT[3_c], arch::OC[2_c][ic<'A'>{}], arch::MOSI[0_c])
                 .attach_pin(18_c, arch::PB[4_c], arch::PCINT[4_c], arch::MISO[0_c])
                 .attach_pin(19_c, arch::PB[5_c], arch::PCINT[5_c], arch::SCK[0_c])
                 .attach_pin(20_c, arch::AVCC)
                 .attach_pin(21_c, arch::AREF)
                 .attach_pin(22_c, arch::GND)
                 .attach_pin(23_c, arch::PC[0_c], arch::PCINT[8_c], arch::ADC[0_c])
                 .attach_pin(24_c, arch::PC[1_c], arch::PCINT[9_c], arch::ADC[1_c])
                 .attach_pin(25_c, arch::PC[2_c], arch::PCINT[10_c], arch::ADC[2_c])
                 .attach_pin(26_c, arch::PC[3_c], arch::PCINT[11_c], arch::ADC[3_c])
                 .attach_pin(27_c, arch::PC[4_c], arch::PCINT[12_c], arch::ADC[4_c], arch::SDA[0_c])
                 .attach_pin(28_c, arch::PC[5_c], arch::PCINT[13_c], arch::ADC[5_c], arch::SCL[0_c]);
//constexpr auto atmega328p_32m1a = 0;
//constexpr auto atmega328p_32a = atmega328p_32m1a;

}}}


#endif
