#ifndef MPL_UNDEFINED_HPP
#define MPL_UNDEFINED_HPP

namespace mpl {


struct undefined { constexpr undefined(){} };

constexpr undefined undef() { return undefined{}; }

}

#endif
