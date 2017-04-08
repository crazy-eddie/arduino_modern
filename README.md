# Modern C++ Arduino Library

This project has not yet gained alpha status.  Use at own risk.

The goal of this project is to create a C++ arduino library that:

* Enforces hardware semantics through type safety.  Can't read an input pin for example.
* Easy to use for everyone.
* Fast - will use C++ metaprogramming through templates and constexpr to make things as fast as possible while not sacrificing interface simplicity.
* Tight - Will use C++ metaprogramming to avoid unnecessary information being embedded into the executable.

# using

## Adding a new platform:

First you must describe your port type.  This is going to have the size of the registers
as well as providing access to them.

Then you create your platform via calls to describe_platform and pass it a platform builder.

Example:

`constexpr auto test = describe_platform(arch_<test_arch_>{}.register_pin(pin1, P0, 1));`

The arguments to `register_pin` are the pin id you want to add, the port it uses, and the pin's bitmask.  Calls to register_pin can be chained.

In the future the interface will be:

`constexpr auto test_platform = describe_platform(platform(test_io).register_pin(pin1, P0, 1));`

## Configuring your pins:

`auto driver = initialize(test_platform.set_mode(pin1, output));`

The arguments to `set_mode` are the pin id you want to set, and the mode you want to set it to.

## Using your pins:

`driver.high(pin1);`

This turns on pin1.

`driver.low(pin1);`

This turns off pin1.

`bool on = driver.read(pin1);`

Reads the value of the digital pin.

You can only use high/low on pins configured for output, and read on pins configured for input.

PWM and analog input pins are not yet supported.

# Roadmap:

In no particular order...

* Devices - you'll be able create new devices or use those available in the library to operate periferals.  They'll remove the pins from both availability and initialization and govern them themselves.  You won't be able to mess with them outside the device.
* Independence from arduino lib - only use the avr c runtime -- no Arduino.h anywhere.
* Port merging - you'll be able to `driver.high(pin1,pin2,pin3);` and it will send one command per port.  Metaprogramming will create the correct mask at compile time and it'll be used to set the pins to high in one call.
* Further safety measures - registering an already registered pin should fail.  registering a new pin with a port/mask combo already registered for another pin should fail.  registering a pin with a mask past the port's capabilities should fail.
* Timers
* PWM - tone/analogWrite
* More devices - things in mind: temp, light, motors, wire
* MySensors compatibility layer: ability to implement MySensors nodes using this lib.
* Lock-in - make it as tough as possible to break through the safety provided.
* Event looping with signal interface.  Utilities to go with.
* All examples from Arduino Starter Kit book translated.