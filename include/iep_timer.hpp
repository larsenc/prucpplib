#ifndef IEP_TIMER_HPP
#define IEP_TIMER_HPP

#include "pru_iep.h"

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


/**
 * The IEPThrottle implements a simple throttle using the IEP peripheral.
 *
 * The IEPThrottle makes sure that the PERIOD amount of cycles(5 ns) elapses between consecutive calls to IEPThrottle::throttle()
 *
 * Limitation: I suspect there will be issues if one tries to use an instance of the IEPThrottle class in both PRUs
 *             since they are acting on the same IEP registers.
 */
template<uint32_t PERIOD>
class IEPThrottle : public IEPTimer
{
public:
    IEPThrottle()
        : IEPTimer()
    {}

    void throttle()
    {
        // Loop until desired PERIOD has passed.
        while(elapsedCycles() <= PERIOD) {}

        resetCounter();
    }
};

} // namespace prucpp

#endif // IEP_TIMER_HPP
