#ifndef GPIO_OUTPUT_HPP
#define GPIO_OUTPUT_HPP

#include <stdint.h>

#include "prucpplib/gpio/gpio.hpp"
#include "prucpplib/register_30.hpp"

namespace prucpp {

template<uint8_t BIT_NR>
class GPIOOutput : public GPIO<GPIOOutput, BIT_NR>
{
public:
    void setValue(bool value) volatile
    {
        // Branch free individual bit set. Source: https://graphics.stanford.edu/~seander/bithacks.html
        __R30 ^= (-value ^ __R30) & GPIO<GPIOOutput, BIT_NR>::BIT_MASK;
    }

    volatile uint32_t& getRegister() volatile
    {
        return __R30;
    }

    const volatile uint32_t& getRegister() const volatile
    {
        return __R30;
    }
};

} // namespace prucpp

#endif // GPIO_OUTPUT_HPP
