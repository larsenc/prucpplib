#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "prucpplib/util/static_assert.hpp"

namespace prucpp {

struct Task
{
    typedef void (*Function)();

    Task(uint32_t wakeup, const Function function)
        : wakeup(wakeup)
        , function(function)
    {} 

    const uint32_t wakeup;
    const Function function;
};


/*
 * The run function implements a simple clock-based task scheduling strategy
*/
template<uint32_t PERIOD, typename TTimer, typename TTask, uint8_t NUM_TASKS>
inline void run(TTimer& timer, TTask (&tasks)[NUM_TASKS])
{
    static_assert_<PERIOD <= TTimer::max_period>();

    uint8_t i = 0;
    timer.resetCounter();
    while(true) {
        while(timer.elapsedCycles() < tasks[i].wakeup){}
        
        tasks[i++].function();

        if (i == NUM_TASKS){
            i = 0;
            while(timer.elapsedCycles() < PERIOD){}
            timer.resetCounter();
        }
    }
}

} // namespace prucpp

#endif // SCHEDULER_H
