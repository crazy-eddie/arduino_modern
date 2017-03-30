#ifndef AVR_HARDWARE_STANDARD_PORTS_HPP
#define AVR_HARDWARE_STANDARD_PORTS_HPP

namespace avr { namespace hardware { namespace standard { namespace ports {

template < typename Port, uint8_t BitMask >
struct pin
{
    static constexpr auto port = Port{};

    static constexpr auto mask = BitMask;
};

#define PORT(X) \
struct P ## X ## _ \
{ \
    static uint8_t volatile* mode_register() { return &DDR ## X ; } \
    static uint8_t volatile* input_register() { return &PIN ## X ; } \
    static uint8_t volatile* output_register() { return &PORT ## X ; } \
    constexpr P ## X ## _ (){} \
}; constexpr P ## X ## _ P ## X

PORT(B);
PORT(C);
PORT(D);



}}}}

#endif
