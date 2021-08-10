#ifndef GPIO_INPUT_HPP
#define GPIO_INPUT_HPP

#include <stdint.h>

#include "prucpplib/gpio/gpio.hpp"
#include "prucpplib/register_31.hpp"

namespace prucpp {

template<uint8_t GPIO_MASK>
class GPIOInput : public GPIO<GPIOInput, GPIO_MASK>
{
public:
    volatile uint32_t& getRegister() volatile
    {
        return __R31;
    }

    const volatile uint32_t& getRegister() const volatile
    {
        return __R31;
    }
};

} // namespace prucpp

#endif // GPIO_INPUT_HPP
