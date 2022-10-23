#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdint.h>

namespace prucpp {

template<template<uint8_t> class TDerived, uint8_t BIT_NR>
class GPIO
{
public:
    typedef TDerived<BIT_NR> derived_type;

    enum {
        BIT_MASK = 1 << BIT_NR
    };

    bool readValue() const volatile
    {
        return ((getRegister() & BIT_MASK) >> BIT_NR);
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
