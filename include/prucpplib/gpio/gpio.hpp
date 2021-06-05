#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdint.h>

namespace prucpp {

template<typename TDerived, uint8_t GPIO_MASK>
class GPIO
{
public:
    bool readValue() const volatile
    {
        return ((getRegister() & (1 << GPIO_MASK)) >> GPIO_MASK);
    }

    volatile uint32_t& getRegister() volatile
    {
        volatile TDerived& derived = static_cast<volatile TDerived&>(*this);
        return derived.getRegister();
    }

    const volatile uint32_t& getRegister() const volatile
    {
        const volatile TDerived& derived = static_cast<const volatile TDerived&>(*this);
        return derived.getRegister();
    }
};

} // namespace prucpp

#endif // GPIO_HPP
