#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdint.h>

#include "register_30.hpp"
#include "register_31.hpp"

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

template<uint8_t GPIO_MASK>
class GPIOOutput : public GPIO<GPIOOutput<GPIO_MASK>, GPIO_MASK>
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

template<uint8_t GPIO_MASK>
class GPIOInput : public GPIO<GPIOOutput<GPIO_MASK>, GPIO_MASK>
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

// P8 - Mode 5
typedef GPIOOutput<15>  pru0_P8_11_out;
typedef GPIOOutput<14>  pru0_P8_12_out;
typedef GPIOInput<15>   pru0_P8_15_in;
typedef GPIOInput<14>   pru0_P8_16_in;
typedef GPIOInput<13>   pru1_P8_20_in;
typedef GPIOInput<12>   pru1_P8_21_in;

typedef GPIOInput<8>    pru1_P8_27_in;
typedef GPIOInput<10>   pru1_P8_28_in;
typedef GPIOInput<9>    pru1_P8_29_in;
typedef GPIOInput<11>   pru1_P8_30_in;

typedef GPIOInput<6>    pru1_P8_39_in;
typedef GPIOInput<7>    pru1_P8_40_in;
typedef GPIOInput<4>    pru1_P8_41_in;
typedef GPIOInput<5>    pru1_P8_42_in;
typedef GPIOInput<2>    pru1_P8_43_in;
typedef GPIOInput<3>    pru1_P8_44_in;
typedef GPIOInput<0>    pru1_P8_45_in;
typedef GPIOInput<1>    pru1_P8_46_in;

// P8 - Mode 6
typedef GPIOOutput<13>  pru1_P8_20_out;
typedef GPIOOutput<12>  pru1_P8_21_out;

typedef  GPIOOutput<8>  pru1_P8_27_out;
typedef  GPIOOutput<10> pru1_P8_28_out;
typedef  GPIOOutput<9>  pru1_P8_29_out;

typedef  GPIOOutput<6>  pru1_P8_39_out;
typedef  GPIOOutput<7>  pru1_P8_40_out;
typedef  GPIOOutput<4>  pru1_P8_41_out;
typedef  GPIOOutput<5>  pru1_P8_42_out;
typedef  GPIOOutput<2>  pru1_P8_43_out;
typedef  GPIOOutput<3>  pru1_P8_44_out;
typedef  GPIOOutput<0>  pru1_P8_45_out;
typedef  GPIOOutput<1>  pru1_P8_46_out;

// P9 - Mode 5
typedef GPIOInput<16>   pru0_P9_24_in;
typedef GPIOInput<7>    pru0_P9_25_in;
typedef GPIOInput<16>   pru1_P9_26_in;
typedef GPIOInput<5>    pru0_P9_27_in;
typedef GPIOInput<3>    pru0_P9_28_in;
typedef GPIOInput<1>    pru0_P9_29_in;
typedef GPIOInput<2>    pru0_P9_30_in;
typedef GPIOInput<0>    pru0_P9_31_in;

typedef GPIOInput<6>    pru0_P9_41B_in;
typedef GPIOInput<4>    pru0_P9_42B_in;

//typedef GPIOInput<15> pru1_na_in;
//typedef GPIOInput<14> pru1_na_in;

// P9 - Mode 6
typedef GPIOOutput<7>   pru0_P9_25_out;
typedef GPIOOutput<5>   pru0_P9_27_out;
typedef GPIOOutput<3>   pru0_P9_28_out;
typedef GPIOOutput<1>   pru0_P9_29_out;
typedef GPIOOutput<2>   pru0_P9_30_out;
typedef GPIOOutput<0>   pru0_P9_31_out;

typedef GPIOOutput<2>   pru0_P9_30_out;
typedef GPIOOutput<0>   pru0_P9_31_out;

typedef GPIOInput<16>   pru0_P9_41A_in;
typedef GPIOOutput<6>   pru0_P9_41B_out;

typedef GPIOOutput<4>   pru0_P9_42B_out;

//typedef GPIOOutput<15> pru1_na_out;
//typedef GPIOOutput<14> pru1_na_in;

#endif // GPIO_HPP
