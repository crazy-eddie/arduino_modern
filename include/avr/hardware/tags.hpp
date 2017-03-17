#ifndef AVR_HARDWARE_TAGS_HPP
#define AVR_HARDWARE_TAGS_HPP

namespace avr { namespace hardware { namespace pin_config {

constexpr struct digital_tag {} digital;
constexpr struct analog_tag {} analog;

constexpr struct input_tag {} input;
constexpr struct input_pull_tag {} input_pull;
constexpr struct output_tag {} output;

// timers to come.

#if 0
template < int I >
struct pin_tag { enum { id = I }; };

template < typename PinTag, typename TypeTag >
struct pin_descriptor
{
    using pin_tag = PinTag;
    using type_tag = TypeTag;

    enum { id = PinTag::value };

    pin_tag pin;
    type_tag type;

    // uint8_t mask;
    // volatile uint8_t* mode_register();
    // volatile uint8_t* input_register();
    // volatile uint8_t* output_register();
};

template < typename PinTag, typename TypeTag, typename ModeTag >
constexpr pin_descriptor<PinTag, TypeTag, ModeTag> create_pin(PinTag,TypeTag,ModeTag)
{
    return pin_descriptor<PinTag,TypeTag,ModeTag>{};
}


template <typename PinDescriptor, typename Next>
struct pin_collection : Next
{
};

struct pins_end
{
    template <uint8_t PinID, typename TypeTag, typename ModeTag>
    using pin_descriptor = pin_descriptor<pin_tag<PinID>,TypeTag,ModeTag>;

    template <uint8_t PinID, typename TypeTag, typename ModeTag>
    using pin_collection = pin_collection<pin_descriptor<PinID,TypeTag,ModeTag>,pins_end>;

    template <uint8_t PinID, typename TypeTag, typename ModeTag>
    constexpr pin_collection<PinID,TypeTag,ModeTag> add_pin(TypeTag, ModeTag)
    {
        return pin_collection<PinID,TypeTag,ModeTag>{};
    }
};

constexpr pins_end configure_pins() { return pins_end{}; }
#endif

}}}

#endif
