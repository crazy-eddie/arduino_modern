#ifndef HARDWARE_CHIP_ATMEGA328P_HPP
#define HARDWARE_CHIP_ATMEGA328P_HPP

#include "../arch/avr.hpp"
#include "../arch/generic/pin.hpp"
#include "../arch/generic/chip_builder.hpp"

namespace crazy_arduino { namespace hardware { namespace chip {

using namespace arch::avr;


constexpr auto atmega328p_28p3 =*
        (PC[6_c])--[ 1_p - U - 28_p]--(PC[5_c])
        (PD[0_c])--[ 2_p   ,   27_p]--(PC[4_c])
        (PD[1_c])--[ 3_p   ,   26_p]--(PC[3_c])
        (PD[2_c])--[ 4_p   ,   25_p]--(PC[2_c])
        (PD[3_c])--[ 5_p   ,   24_p]--(PC[1_c])
        (PD[4_c])--[ 6_p   ,   23_p]--(PC[0_c])
            (VCC)--[ 7_p   ,   22_p]--(GND)
            (GND)--[ 8_p   ,   21_p]--(AREF)
        (PB[6_c])--[ 9_p   ,   20_p]--(AVCC)
        (PB[7_c])--[10_p   ,   19_p]--(PB[5_c])
        (PD[5_c])--[11_p   ,   18_p]--(PB[4_c])
        (PD[6_c])--[12_p   ,   17_p]--(PB[3_c])
        (PD[7_c])--[13_p   ,   16_p]--(PB[2_c])
        (PB[0_c])--[14_p - _ - 15_p]--(PB[1_c]);

}}}


#endif
