#ifndef ECAP_PWM_H
#define ECAP_PWM_H

#include <pru_ecap.h>

namespace prucpp {

/*
 * The ECAPPWM class wraps PWM functionality from the eCap0 peripheral.
 *
 * Beaglebone black uses pins:
 *      - P9_42 : mode 3 - pru_ecap
 */

template<uint32_t PERIOD>
struct ECAPPWM
{
    ECAPPWM(uint32_t cyclesHigh = 0)
    {
        // Enable APWM mode and enable asynchronous operation
        // Set polarity to active high
        CT_ECAP.ECCTL2 = 0x02C0;

        // Set number of clock cycles in the PWM period
        CT_ECAP.CAP1 = PERIOD;

        // Enable ECAP PWM freerun counter
        CT_ECAP.ECCTL2 |= 0x0010;

        // Set the duty cycle
        CT_ECAP.CAP2 = cyclesHigh;
    }

    /*
     * Set the duty cycle by specifying number of cycles the signal is high during a period.
     * The duty cycle is equal to: numCyclesHigh/PERIOD
     */
    void setDutyCycle(uint32_t cyclesHigh)
    {
        CT_ECAP.CAP2 = cyclesHigh;
    }
};

} // namespace prucpp

#endif // ECAP_PWM_H
