#ifndef AVR_HARDWARE_CONFIGURATOR_HPP
#define AVR_HARDWARE_CONFIGURATOR_HPP


namespace avr { namespace hardware {

struct unset_mode
{
    constexpr unset_mode() {}
};

template < typename PinDesc, typename Mode = unset_mode >
struct pin_config_
{
    constexpr pin_config_() {}

    static constexpr bool unset() { return false; }

    template < typename PinTag, typename NewMode >
    static constexpr pin_config_ set_mode(PinTag,NewMode) { return pin_config_{}; }

    template < typename NewMode >
    static constexpr pin_config_ set_mode(typename PinDesc::pin_t, NewMode) = delete;

    using pin_t = PinDesc;
    using mode_t = Mode;

    static constexpr pin_t pin = pin_t{};
    static constexpr mode_t mode = mode_t{};
};

template < typename PinDesc >
struct pin_config_<PinDesc, unset_mode>
{
    constexpr pin_config_() {}

    template < typename PinTag, typename Mode >
    static constexpr pin_config_ set_mode(PinTag, Mode) { return pin_config_{}; }

    template < typename Mode >
    static constexpr pin_config_<PinDesc, Mode> set_mode(typename PinDesc::pin_t, Mode)
    {
        return pin_config_<PinDesc, Mode>{};
    }

    static constexpr bool unset() { return true; }

    using pin_t = PinDesc;
    using mode_t = unset_mode;

    static constexpr pin_t pin = pin_t{};
    static constexpr mode_t mode = mode_t{};

};


template < typename ... PinConfig >
struct pin_collection
{
    template < typename PinTag, typename Mode >
    static constexpr auto set_mode(PinTag pin, Mode mode) -> pin_collection<decltype(PinConfig::set_mode(pin,mode))...>
    {
        return pin_collection<decltype(PinConfig::set_mode(pin,mode))...>{};
    }
};

template < typename ... Devices >
struct device_collection
{
    constexpr device_collection(){}

    template < typename Device >
    static constexpr device_collection<Devices..., Device> add(Device) { return device_collection<Devices..., Device>{}; }
};


template < typename Ops, typename Pins, typename Devices >
struct configurator_
{
    constexpr configurator_() {}

    template < typename PinCollection, typename DeviceCollection >
    static constexpr configurator_<Ops, PinCollection, DeviceCollection> create_config(PinCollection,DeviceCollection)
    {
        return configurator_<Ops, PinCollection, DeviceCollection>{};
    }

    template < typename Pin, typename Mode >
    static constexpr auto set_mode(Pin pin, Mode mode) -> decltype(create_config(Pins::set_mode(pin, mode),Devices{}))
    {
        return create_config(Pins::set_mode(pin, mode),Devices{});
    }

    //template < typename PinTag, typename Mode >
    //static constexpr auto set_mode(PinTag pin, Mode mode) -> configurator_<Ops, decltype(PinConfig::set_mode(pin,mode))...>
    //{
    //    return configurator_<Ops, decltype(PinConfig::set_mode(pin,mode))...>{};
    //}

    template < typename Device >
    static constexpr auto add_device(Device device) -> decltype(device.configure(configurator_{}))
    {
        return device.configure(configurator_<Ops,Pins,Devices>{});
    }

    using io_t = Ops;
    static constexpr auto io = io_t{};

    using pins_t = Pins;
    static constexpr auto pins = pins_t{};

    using devices_t = Devices;
    static constexpr auto devices = devices_t{};
};

template < typename Ops, typename ... PinDesc >
using configurator = configurator_< Ops, pin_collection<pin_config_<PinDesc> ...>, device_collection<> >;

}}



#endif
