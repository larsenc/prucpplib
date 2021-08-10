#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdint.h>

namespace prucpp {

template<template<uint8_t> class TDerived, uint8_t GPIO_MASK>
class GPIO
{
public:
    typedef GPIO<TDerived, GPIO_MASK> derived_type;

    bool readValue() const volatile
    {
        return ((getRegister() & (1 << GPIO_MASK)) >> GPIO_MASK);
    }

    volatile uint32_t& getRegister() volatile
    {
        volatile derived_type& derived = static_cast<volatile derived_type&>(*this);
        return derived.getRegister();
    }

    const volatile uint32_t& getRegister() const volatile
    {
        const volatile derived_type& derived = static_cast<const volatile derived_type&>(*this);
        return derived.getRegister();
    }
};

} // namespace prucpp

#endif // GPIO_HPP
