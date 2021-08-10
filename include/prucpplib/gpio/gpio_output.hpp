#ifndef GPIO_OUTPUT_HPP
#define GPIO_OUTPUT_HPP

#include <stdint.h>

#include "prucpplib/gpio/gpio.hpp"
#include "prucpplib/register_30.hpp"

namespace prucpp {

template<uint8_t GPIO_MASK>
class GPIOOutput : public GPIO<GPIOOutput, GPIO_MASK>
{
public:
    void setValue(bool value) volatile
    {
        getRegister() = (value << GPIO_MASK);
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
