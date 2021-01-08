#ifndef IEP_TIMER_HPP
#define IEP_TIMER_HPP

#include "pru_iep.h"

namespace prucpp {

/**
 * The IEPTimer implements a simple timer using the IEP peripheral.
 *
 * The IEPTimer makes sure that the PERIOD amount of cycles(5 ns) elapses between consecutive calls to IEPTimer::throttle()
 *
 * Limitation: I suspect there will be issues if one tries to use an instance of the IEPTimer class in both PRUs
 *             since they are acting on the same IEP registers.
 */
template<uint32_t PERIOD>
class IEPTimer
{
public:
    IEPTimer()
    {
        resetCounter();
    }

    void throttle()
    {
        // Loop until desired PERIOD has passed.
        while(CT_IEP.TMR_CNT <= PERIOD) {}

        resetCounter();
    }

private:
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
