#include "process.hpp"

proc::Process::Process()  noexcept :
    mTimeLimit      (MAX_TIME_LIMIT),
    mMemoryLimit    (MAX_MEMORY_LIMIT)
{}

//--------------------------------------------------------------------------------

void
proc::Process::setLimits(uint_64 aTimeLimit, uint_64 aMemoryLimit) noexcept
{
    if (aTimeLimit > MAX_TIME_LIMIT) aTimeLimit = MAX_TIME_LIMIT;
    if (aMemoryLimit > MAX_MEMORY_LIMIT) aMemoryLimit = MAX_MEMORY_LIMIT;

    mTimeLimit = aTimeLimit;
    mMemoryLimit = aMemoryLimit;
}

//--------------------------------------------------------------------------------