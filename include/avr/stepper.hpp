#ifndef AVR_STEPPER_HPP
#define AVR_STEPPER_HPP

namespace avr {

// gear_train of gears.
// each gear has a tooth count....actually gears can have multiple output teeth.
// attaching a motor to one end of the gear train will compute
//    gear ratio of train using drivin/drive
// mechanical advantage can also be computed.

// Motor first, gears later.

// step motors have a step count per revolution.  For now at least they also have a turn ratio.
//   calculate angle of one step on motor.
//   apply ratio of gear train to get angle of output per step.
//   use this angle to calculate the step count needed to turn x deg/rad
//   also use to calculate speed of signal to create given rpm.

template < int Input, int Output >
struct gear_train
{
    static constexpr double ratio = static_cast<double>(Input) / static_cast<double>(Output);
};

}

#endif
