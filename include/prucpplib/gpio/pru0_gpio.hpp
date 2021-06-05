#ifndef PRU0_GPIO_HPP
#define PRU0_GPIO_HPP

#include "prucpplib/gpio/gpio_input.hpp"
#include "prucpplib/gpio/gpio_output.hpp"

namespace prucpp {

/**
 *  PRU0 Inputs
 */
// P8 - Mode 5
typedef GPIOInput<15>   pru0_P8_15_in;
typedef GPIOInput<14>   pru0_P8_16_in;

// P9 - Mode 5
typedef GPIOInput<16>   pru0_P9_24_in;
typedef GPIOInput<7>    pru0_P9_25_in;
typedef GPIOInput<5>    pru0_P9_27_in;
typedef GPIOInput<3>    pru0_P9_28_in;
typedef GPIOInput<1>    pru0_P9_29_in;
typedef GPIOInput<2>    pru0_P9_30_in;
typedef GPIOInput<0>    pru0_P9_31_in;

typedef GPIOInput<6>    pru0_P9_41B_in;
typedef GPIOInput<4>    pru0_P9_42B_in;

/**
 *  PRU0 Outputs
 */
// P8 - Mode 5
typedef GPIOOutput<15>  pru0_P8_11_out;
typedef GPIOOutput<14>  pru0_P8_12_out;

// P9 - Mode 6
typedef GPIOOutput<7>   pru0_P9_25_out;
typedef GPIOOutput<5>   pru0_P9_27_out;
typedef GPIOOutput<3>   pru0_P9_28_out;
typedef GPIOOutput<1>   pru0_P9_29_out;
typedef GPIOOutput<2>   pru0_P9_30_out;
typedef GPIOOutput<0>   pru0_P9_31_out;

typedef GPIOOutput<2>   pru0_P9_30_out;
typedef GPIOOutput<0>   pru0_P9_31_out;

typedef GPIOOutput<6>   pru0_P9_41B_out;
typedef GPIOOutput<4>   pru0_P9_42B_out;

} // namespace prucpp

#endif // PRU0_GPIO_HPP
