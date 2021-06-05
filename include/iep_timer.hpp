#ifndef IEP_TIMER_HPP
#define IEP_TIMER_HPP

#include "pru_iep.h"

#include <limits.h>

namespace prucpp {


/**
 * The IEPTimer allows one to calculate the amount of elapsed cycles(5 ns).
 *
 * Limitation: I suspect there will be issues if one tries to use an instance of the IEPTimer class in both PRUs
 *             since they are acting on the same IEP registers.
 */
class IEPTimer
{
public:
    static const uint32_t max_period = UINT_MAX;

    IEPTimer()
    {
        resetCounter();
    }

    uint32_t elapsedCycles() const
    {
        return CT_IEP.TMR_CNT;
    }

    void resetCounter()
    {
        // Set the counter to zero
        CT_IEP.TMR_CNT = 0x0;

        // Set the global configure to 10001
        //  - Enable the counter (bit 0)
        //  - Define the default increment value as 1 (bit 4-7)
        CT_IEP.TMR_GLB_CFG = 0x11;
    }
};

} // namespace prucpp

#endif // IEP_TIMER_HPP
