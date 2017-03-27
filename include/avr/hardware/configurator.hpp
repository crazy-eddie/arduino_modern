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

};

template < typename ... PinConfig >
struct configurator_
{
    constexpr configurator_() {}

    template < typename PinTag, typename Mode >
    static constexpr auto set_mode(PinTag pin, Mode mode) -> configurator_<decltype(PinConfig::set_mode(pin,mode))...>
    {
        return configurator_<decltype(PinConfig::set_mode(pin,mode))...>{};
    }
};

template < typename ... PinDesc >
using configurator = configurator_< pin_config_<PinDesc> ... >;

}}



#endif
