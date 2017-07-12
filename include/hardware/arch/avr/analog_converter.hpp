#ifndef  HARDWARE_ARCH_AVR_ANALOG_CONVERTER_HPP
#define  HARDWARE_ARCH_AVR_ANALOG_CONVERTER_HPP


namespace crazy_arduino { namespace hardware { namespace arch { namespace avr_detail {

template < int Idx >
struct adc_channel
{
    constexpr adc_channel(){}
};

struct analog_converter
{
    constexpr analog_converter(){}

    template < typename Idx >
    constexpr auto operator[](Idx) const
    {
        return adc_channel<Idx::value()>{};
    }
};

}}}}

#endif
