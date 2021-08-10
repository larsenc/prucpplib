# prucpplib

prucpplib is a header only library that contains a set of functions and classes that aims to make it easier to develop pru applications with c++.

prucpplib is being developed with AM335x processors in mind and tested on a BeagleBone Black.

## Example
```c++
#include "prucpplib/resource_table_0.h"

#include "prucpplib/gpio/pru0_gpio.hpp"
#include "prucpplib/scheduler/scheduler.hpp"
#include "prucpplib/timer/iep_timer.hpp"
#include "prucpplib/timer/periods.hpp"

#include <am335x/pru_cfg.h>
#include <rsc_types.h>

using namespace prucpp;
using namespace prucpp::beaglebone_black;

volatile pru0_P9_27_out out1;
volatile pru0_P9_28_out out2;

void toggle1()
{
    out1.setValue(true);
    __delay_cycles(DURATION_100µs);
    out1.setValue(false);
}

void toggle2()
{
    out2.setValue(true);
    __delay_cycles(DURATION_200µs);
    out2.setValue(false);
}

void main(void) {
    Task tasks[] = {
        Task(0, &toggle1),
        Task(DURATION_500µs, &toggle2)
    };
    IEPTimer timer;
    run<PERIOD_1kHz>(timer, tasks);
}
```