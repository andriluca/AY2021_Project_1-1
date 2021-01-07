/* =========================================================================
 * Project01-1, Luca Andriotto, Matteo Cavicchioli, Alessandro Pirelli
 * =========================================================================
*/

#ifndef __INTERRUPT_H

    #define __INTERRUPT_H

    #include "cytypes.h"
    #include "define.h"
    #include "I2c.h"

    // Flags
    volatile uint8_t t_isr;                 // Used to sync Temperature sampling.
    volatile uint8_t wtm;                   // Used to sync Accelerations sampling.
    volatile uint8_t comm_rec;              // Used in case of a byte being received.
    volatile uint8_t isButtonReleased;      // True when button has been released.
    volatile uint8_t boot;                  // These last 2 flags are used during the booting time.
    volatile uint8_t trigger;               

    volatile uint16_t counted_seconds;      // Storing the duration of button pressing.

    // Watermark ISR
    CY_ISR_PROTO(WTM_ISR);

    // Temperature ISR
    CY_ISR_PROTO(TEMP_ISR);

    // UART ISR
    CY_ISR_PROTO(COMM_GUI);

    // Switch ISR
    CY_ISR_PROTO(COUNT_SEC);

#endif
