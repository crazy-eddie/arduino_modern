#ifndef AVR_HARDWARE_INITIALIZE_HPP
#define AVR_HARDWARE_INITIALIZE_HPP

//#include "configurator.hpp"
//#include "driver.hpp"

#include "../../mpl/util.hpp"

namespace avr { namespace hardware {


template < typename HardwareConfig >
auto initialize(HardwareConfig hardware_config)
{
    mpl::for_each( hardware_config.configured()
                 , [=] (auto pin)
                   {
                       hardware_config.io().set_mode(pin.pin_desc, pin.mode);
                   });

    return false;
}

}}

#endif
