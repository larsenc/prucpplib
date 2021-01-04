#ifndef EQEP_POSITION_ENCODER_1_HPP
#define EQEP_POSITION_ENCODER_1_HPP

#include <sys_pwmss.h>

#include "eqep_position_encoder.hpp"

#define CM_PER_EPWMSS1 (*((volatile unsigned int *)0x44E000CC))

/*
 * Position encoder abstraction using the eQep module of PWMSS1
 *
 * Uses pins:
 *      - P8_33 : mode 2
 *      - P8_35 : mode 2
 */
template<uint16_t QCAPCTL, uint32_t QUPRD>
struct EQepPositionEncoder1 : public detail::EQepPositionEncoder<QCAPCTL, QUPRD>
{
    EQepPositionEncoder1()
        : detail::EQepPositionEncoder<QCAPCTL, QUPRD>(PWMSS1)
    {
        // Enable PWMSS1 clock signal generation for pwm subsystem 1
        while (!(CM_PER_EPWMSS1 & 0x2)) {
            CM_PER_EPWMSS1 |= 0x2;
        }
    }
};


#endif // EQEP_POSITION_ENCODER_1_HPP
