#ifndef PRU1_GPIO_HPP
#define PRU1_GPIO_HPP

#include "gpio_input.hpp"
#include "gpio_output.hpp"

namespace prucpp {

/**
 *  PRU1 Inputs
 */
// P8 - Mode 5
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
typedef GPIOInput<16>   pru1_P9_26_in;

/**
 *  PRU1 Outputs
 */
// P8 - Mode 6
typedef GPIOOutput<13>  pru1_P8_20_out;
typedef GPIOOutput<12>  pru1_P8_21_out;

typedef GPIOOutput<8>  pru1_P8_27_out;
typedef GPIOOutput<10> pru1_P8_28_out;
typedef GPIOOutput<9>  pru1_P8_29_out;

typedef GPIOOutput<6>  pru1_P8_39_out;
typedef GPIOOutput<7>  pru1_P8_40_out;
typedef GPIOOutput<4>  pru1_P8_41_out;
typedef GPIOOutput<5>  pru1_P8_42_out;
typedef GPIOOutput<2>  pru1_P8_43_out;
typedef GPIOOutput<3>  pru1_P8_44_out;
typedef GPIOOutput<0>  pru1_P8_45_out;
typedef GPIOOutput<1>  pru1_P8_46_out;

// Not used
//typedef GPIOInput<15> pru1_na_in;
//typedef GPIOInput<14> pru1_na_in;
//typedef GPIOOutput<15> pru1_na_out;
//typedef GPIOOutput<14> pru1_na_out;

} // namespace prucpp

#endif // PRU1_GPIO_HPP
