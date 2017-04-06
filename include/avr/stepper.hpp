#ifndef AVR_STEPPER_HPP
#define AVR_STEPPER_HPP

namespace avr {

template < typename T >
T&& declval();

struct steps
{
    constexpr steps(int i) : count{i} {}

    int count;
};

struct phases
{
    constexpr phases(int i) : count{i} {}

    int count;
};

struct stepper_motor
{
    constexpr stepper_motor(avr::steps s, avr::phases p) : steps_{s}, phases_{p} {}

    constexpr auto steps() -> decltype(declval<avr::steps>().count) { return steps_.count; }
    constexpr auto phases() -> decltype(declval<avr::phases>().count) { return phases_.count; }

private:
    avr::steps steps_;
    avr::phases phases_;
};

constexpr stepper_motor stepper(steps s, phases p) { return stepper_motor{s,p}; }

}

#endif
