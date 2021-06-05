#ifndef ECAP_PWM_H
#define ECAP_PWM_H

#include <pru_ecap.h>

namespace prucpp {

/*
 * The ECAPPWM class wraps PWM functionality from the eCap0 peripheral.
 *
 * It uses pin 9_42 configured in MUX_MODE3/pru_ecap.
 * Before loading and running the firmware that uses this class, call
 * configure pin 9_42: "$ config-pin -a P9_42 pru_ecap"
*/
template<uint32_t PERIOD>
struct ECAPPWM
{
    ECAPPWM(uint32_t numCyclesHigh = 0)
    {
        // Enable APWM mode and enable asynchronous operation
        // Set polarity to active high
        CT_ECAP.ECCTL2 = 0x02C0;

        // Set number of clock cycles in the PWM period
        CT_ECAP.CAP1 = PERIOD;

        // Enable ECAP PWM freerun counter
        CT_ECAP.ECCTL2 |= 0x0010;

        // Set the duty cycle
        CT_ECAP.CAP2 = numCyclesHigh;
    }

    /*
     * Set the duty cycle by specifying number of cycles the signal is high during a period.
     * The duty cycle is equal to: numCyclesHigh/PERIOD
     */
    void setDutyCycle(uint32_t numCyclesHigh)
    {
        CT_ECAP.CAP2 = numCyclesHigh;
    }
};

} // namespace prucpp

#endif // ECAP_PWM_H
