#ifndef GPIO_INPUT_HPP
#define GPIO_INPUT_HPP

#include <stdint.h>

#include "gpio.hpp"
#include "register_31.hpp"

template<uint8_t GPIO_MASK>
class GPIOInput : public GPIO<GPIOInput<GPIO_MASK>, GPIO_MASK>
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

#endif // GPIO_INPUT_HPP
