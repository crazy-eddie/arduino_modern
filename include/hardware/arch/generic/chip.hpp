#ifndef HARDWARE_ARCH_GENERIC_CHIP_HPP
#define HARDWARE_ARCH_GENERIC_CHIP_HPP


namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

template < typename PinCollection >
struct chip : PinCollection
{
    constexpr chip() {}
};

}}}}


#endif
