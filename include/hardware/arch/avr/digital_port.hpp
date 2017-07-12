#ifndef  HARDWARE_ARCH_AVR_DIGITAL_PORT_HPP
#define  HARDWARE_ARCH_AVR_DIGITAL_PORT_HPP

namespace crazy_arduino { namespace hardware { namespace arch { namespace avr_detail {

template < typename Port, int Idx >
struct digital_io_pin
{
    constexpr digital_io_pin(){}
};

template < int Idx >
struct digital_port
{
    constexpr digital_port() {}

    template < typename PIdx >
    constexpr auto operator[](PIdx) const
    {
        return digital_io_pin<digital_port, PIdx::value()>{};
    }
};

template < int Idx >
constexpr auto port() { return digital_port<Idx>{}; }

template < typename Idx >
constexpr auto port(Idx) { return digital_port<Idx::value()>{}; }

}}}}

#endif
