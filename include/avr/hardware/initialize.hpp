#ifndef AVR_HARDWARE_INITIALIZE_HPP
#define AVR_HARDWARE_INITIALIZE_HPP

//#include "configurator.hpp"
//#include "driver.hpp"

#include "../../mpl/util.hpp"
#include "driver.hpp"

// TODO: Can probably eliminate this by sticking the initialization into the pin itself
//       as a static initialization.  Thus you'd go: auto const pin = hardware_config.pin(pin1)
//       When that pin is instantiated the member will be initialized before main and the
//       routine to do so will call set_mode.

namespace avr { namespace hardware {


template < typename HardwareConfig >
auto initialize(HardwareConfig hardware_config)
{
    mpl::for_each( hardware_config.configured()
                 , [=] (auto pin)
                   {
                       hardware_config.io().set_mode(pin.value().pin_desc, pin.value().mode);
                   });

    return create_driver(hardware_config);
}

}}

#endif
