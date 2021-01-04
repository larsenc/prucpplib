#ifndef ECAPPWM_H
#define ECAPPWM_H

#include <am335x/pru_ecap.h>

// Predefined PWM cycles
#define CYCLE_24_41_kHz   0x2000  // 24.41 kHz
#define CYCLE_48_82_kHz   0x1000  // 48.82 kHz
#define CYCLE_97_66_kHz   0x800   // 97.66 kHz

/*
 * This class uses the eCap0 module accessible for the PRU's.
 *
 * It uses pin 9_42 configured in MUX_MODE3/pru_ecap.
 * Before loading and running the firmware that uses this class, call
 * configure pin 9_42: "$ config-pin -a P9_42 pru_ecap"
*/

template<uint16_t CYCLE>
struct ECAPPWM
{
    ECAPPWM()
    {
        // Enable APWM mode and enable asynchronous operation; set polarity to active high
        CT_ECAP.ECCTL2 = 0x02C0;

        // Set number of clk cycles in a PWM period (APRD)
        CT_ECAP.CAP1 = CYCLE;

        // Enable ECAP PWM Freerun counter
        CT_ECAP.ECCTL2 |= 0x0010;
    }

    void setPeriod(uint16_t period)
    {
        // period < CYCLE
        // Should I enforce this?
        CT_ECAP.CAP2_bit.CAP2 = period;
    }
};

#endif // ECAPPWM_H
