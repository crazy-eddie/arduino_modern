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

template < typename Ops, typename ... PinConfig >
struct configurator_
{
    constexpr configurator_() {}

    template < typename PinTag, typename Mode >
    static constexpr auto set_mode(PinTag pin, Mode mode) -> configurator_<Ops, decltype(PinConfig::set_mode(pin,mode))...>
    {
        return configurator_<Ops, decltype(PinConfig::set_mode(pin,mode))...>{};
    }
};

template < typename Ops, typename ... PinDesc >
using configurator = configurator_< Ops, pin_config_<PinDesc> ... >;

}}



#endif
