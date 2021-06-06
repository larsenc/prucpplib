#ifndef EQEP_POSITION_ENCODER_HPP
#define EQEP_POSITION_ENCODER_HPP

#include <limits.h>
#include <stdint.h>
#include <sys_pwmss.h>

namespace prucpp {
namespace detail {

/*
 * EQepPositionEncoder represents a position encoder.
 *
 * It will configure the eQep module of the pwm subsystem to use
 * Quadrature-count mode and capture the position count every unit time.
 */
template<uint16_t QCAPCTL, uint32_t QUPRD>
class EQepPositionEncoder
{
public:
    EQepPositionEncoder(volatile sysPwmss& pwmSS)
        : mPwmSS(pwmSS)
    {
        // Set to defaults in quadrature mode
        mPwmSS.EQEP_QDECCTL = 0x00;

        // Enable unit timer                                        UTE     = 1
        // Enable capture latch on unit time out                    QCLM    = 1
        // Enable quadrature position counter                       PHEN    = 1
        // Enable software loading of position counter              SWI     = 1
        // Position counter reset on the maximum position           PRCM    = 01
        //
        // PRCM    |SEI    |IEI    |SWI    |SEL    |IEL    |PHEN   |QCLM   |UTE    |WDE
        // 01      |00     |00     |1      |0      |00     |1      |1      |1      |0
        //
        // 01000010001110 = 0x108E
        //
        mPwmSS.EQEP_QEPCTL = 0x108E;


        // Set prescalers for EQEP Capture timer and UPEVNT
        // Note: EQEP Capture unit must be disabled before changing prescalar.( field 15/CEN in QCAPCTL)
        // This register controls the:
        //      - UPPS - Unit position event prescaler      : bit 3-0
        //      - CCPS - eQEP capture timer clock prescaler : bit 6-4
        mPwmSS.EQEP_QCAPCTL = QCAPCTL;

        // Enable EQEP Capture unit
        mPwmSS.EQEP_QCAPCTL |= 0x8000;

        // Enable unit time out interrupt
        mPwmSS.EQEP_QEINT |= 0x0800;

        // Clear encoder count
        mPwmSS.EQEP_QPOSCNT_bit.QPOSCNT = 0x00000000;

        // Set max encoder count
        mPwmSS.EQEP_QPOSMAX_bit.QPOSMAX = UINT_MAX;

        // Clear timer
        mPwmSS.EQEP_QUTMR_bit.QUTMR = 0x00000000;

        // Set "Unit time event" period count
        //      mPwmSS.EQEP_QUPRD_bit.QUPRD = number of 100MHz cycles
        //      Formula: "dT" / (10.0 * 0.000000001)
        // "Unit time event" defines the period of sensors readings. When a new reading is available the interrupt flag
        // EQEP_QFLG is set. When interrupt EQEP_QFLG occurs, mPwmSS.EQEP_QPOSLAT contains the position count since last interrupt.
        mPwmSS.EQEP_QUPRD_bit.QUPRD = QUPRD;

        // Clear all interrupt bits
        // The interrupt service routine will need to clear the global interrupt flag bit and the serviced event,
        // via the interrupt clear register (QCLR), before any other interrupt pulses are generated.
        // Clears the interrupt bit mPwmSS.EQEP_QFLG for example.
        mPwmSS.EQEP_QCLR = 0xFFFF;
    }

    void readPosition(int& position) const volatile
    {
        position = mPwmSS.EQEP_QPOSLAT;
    }

    bool overflowError() volatile
    {
        // Check the COEF bit in the status register EQEP_QEPSTS for overflow error
        if (mPwmSS.EQEP_QEPSTS & 0x08){
            mPwmSS.EQEP_QEPSTS |= 0x08;
            return true;
        }
        return false;
    }

    bool directionError() volatile
    {
        // Check the CDEF bit in the status register EQEP_QEPSTS for direction change error
        if (mPwmSS.EQEP_QEPSTS & 0x10){
            mPwmSS.EQEP_QEPSTS |= 0x10;
            return true;
        }
        return false;
    }

    bool positionChanged() volatile
    {
        // Checks if unit time event has occurred
        if (mPwmSS.EQEP_QFLG & 0x0800) {
            mPwmSS.EQEP_QCLR |= 0x0800;
            return true;
        }
        return false;
    }

private:
    volatile sysPwmss& mPwmSS;
};

} // namespace detail
} // namespace prucpp

#endif // EQEP_POSITION_ENCODER_HPP
