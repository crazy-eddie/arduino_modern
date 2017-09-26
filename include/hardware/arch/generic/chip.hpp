#ifndef HARDWARE_ARCH_GENERIC_CHIP_HPP
#define HARDWARE_ARCH_GENERIC_CHIP_HPP

#include "../../../mpl/collection.hpp"


namespace crazy_arduino { namespace hardware { namespace arch { namespace generic {

template < typename Chip, typename Mapping >
struct mapped
{
    constexpr mapped() {}

    template < typename Pin >
    static constexpr auto get(Pin pin) { return Chip::get(Mapping::get(pin)); }

    static constexpr auto chip = Chip{};
    static constexpr auto mapping = Mapping{};
};

template < typename PinCollection, typename Mapping = mpl::lookup_collection >
struct chip : PinCollection
{
    constexpr chip() {}

    template < typename ChipPin, typename ReMap >
    static constexpr auto map_pin(ChipPin pin,ReMap remap)
    {
        using mapping = decltype(Mapping().insert(remap, pin));
        return chip<PinCollection,mapping>{};
    }

    constexpr mapped<chip,Mapping> operator *() const
    {
        return mapped<chip,Mapping>{};
    }
};

}}}}


#endif
