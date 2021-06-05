#ifndef ELAPSE_HPP
#define ELAPSE_HPP

namespace prucpp {

template<typename TTimer>
void elapseAbsolute(TTimer& timer, const uint32_t& absoluteCycles)
{
    // Loop until desired cycles has elapse.
    while(timer.elapsedCycles() <= absoluteCycles) {}
}

template<typename TTimer>
void elapseRelative(TTimer& timer, const uint32_t& relativeCycles)
{
    const uint32_t absoluteCycles = timer.elapsedCycles() + relativeCycles;
    elapseAbsolute(timer, absoluteCycles);
}

} // namespace prucpp

#endif // ELAPSE_HPP
